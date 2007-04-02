/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2007 Benjamin Schleimer <bensch128@yahoo.com>
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "LineSampler.h"

#include <stdlib.h>
#include <vector>

#include <klocale.h>
#include <kiconloader.h>
#include <kinstance.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>
#include <ktempfile.h>
#include <kdebug.h>
#include <kgenericfactory.h>

#include <kis_iterators_pixel.h>
#include <kis_filter_registry.h>
#include <kis_global.h>
#include <kis_types.h>
#include <kis_selection.h>

#include <qimage.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qpainter.h>

#include "LineSamplerWdg.h"
#include "LineSamplerConfig.h"

typedef KGenericFactory<KritaLineSampler> KritaLineSamplerFactory;
K_EXPORT_COMPONENT_FACTORY( kritaLineSampler, KritaLineSamplerFactory( "krita" ) )

KritaLineSampler::KritaLineSampler(QObject *parent, const char *name, const QStringList &)
: KParts::Plugin(parent, name)
{
    setInstance(KritaLineSamplerFactory::instance());

    kdDebug(41006) << "Line Sampler tools plugin. Class: "
    << className()
    << ", Parent: "
    << parent -> className()
    << "\n";

    if(parent->inherits("KisFilterRegistry"))
    {
        KisFilterRegistry * manager = dynamic_cast<KisFilterRegistry *>(parent);
        manager->add(new KisLineSamplerFilter());
    }
}

KritaLineSampler::~KritaLineSampler()
{
}

KisLineSamplerFilter::KisLineSamplerFilter() 
    : KisFilter(id(), "linesampler", i18n("&LineSampler..."))
    , m_config(NULL)
{

}

/**
 * NOTE: We ignore the rect because it is the bounding rect of the selection and 
 * we want the bounds of the whole image.
 */
void KisLineSamplerFilter::process(KisPaintDeviceSP src, KisPaintDeviceSP dst, 
                                   KisFilterConfiguration* config, const QRect& rect ) 
{
    Q_ASSERT(src != 0);
    Q_ASSERT(dst != 0);
    
    int numberOfLines = static_cast<LineSamplerFilterConfig*>(config)->NumberOfLines();
    QColor color = static_cast<LineSamplerFilterConfig*>(config)->Color();

    kdDebug(41006) << "KisLineSamplerFilter::process: number of lines = " << numberOfLines << "\n";

    QImage image = src->convertToQImage(0);

    QPixmap pixmap;
    Q_ASSERT(pixmap.convertFromImage(image));

    QPainter p;

    QBitmap mask(pixmap.size(), true);

    p.begin(&mask);
    {
        p.setPen(Qt::color1);

        for(int i=0; i<numberOfLines; i++)
        {
            QPoint first, second;
            // Randomly choose the edges which the line will go through
            int orientation = rand() % 6;
            switch(orientation)
            {
            case(0): // go through left and top edges
                first.setX(rect.left()); first.setY(rand()%rect.height()+rect.top());
                second.setX(rand()%rect.width()+rect.left()); second.setY(rect.top());
                break;
            case(1): // go through left and right edges
                first.setX(rect.left()); first.setY(rand()%rect.height()+rect.top());
                second.setX(rect.right()); second.setY(rand()%rect.height()+rect.top());
                break;
            case(2): // go through left and bottom edges
                first.setX(rect.left()); first.setY(rand()%rect.height()+rect.top());
                second.setX(rand()%rect.width()+rect.left()); second.setY(rect.bottom());
                break;
            case(3): // go through top and bottom edges
                first.setX(rand()%rect.width()+rect.left()); first.setY(rect.top());
                second.setX(rand()%rect.width()+rect.left()); second.setY(rect.bottom());
                break;
            case(4): // go through top and right edges
                first.setX(rand()%rect.width()+rect.left()); first.setY(rect.top());
                second.setX(rect.right()); second.setY(rand()%rect.height()+rect.top());
                break;
            case(5): // go through bottom and right edges
                first.setX(rand()%rect.width()+rect.left()); first.setY(rect.bottom());
                second.setX(rect.right()); second.setY(rand()%rect.height()+rect.top());
                break;
            default: Q_ASSERT(false); break;
            }

            p.drawLine(first, second);
        }
    }
    p.end();

    pixmap.setMask(mask);

    image = pixmap.convertToImage();

    dst->convertFromQImage(image, "");

    // Fill in the blanks with black. Make this selectable
    KisRectIteratorPixel it = dst->createRectIterator(rect.x(), rect.y(), rect.width(), rect.height(),
                                                      true);
    KisColorSpace* cs = dst->colorSpace();
    while(it.isDone() == false)
    {
        if(cs->getAlpha(it.rawData()) < 128)
        {
            cs->fromQColor(color, it.rawData());
        }
        ++it;
    }

    // NOTE TO DEVELOPERS: Progress state should be following RAII.
    setProgressDone(); // Must be called even if you don't really support progression
}

KisFilterConfigWidget * KisLineSamplerFilter::createConfigurationWidget(QWidget* parent, 
                                                                        KisPaintDeviceSP /*dev*/)
{       
    return new LineSamplerWdg(static_cast<LineSamplerFilterConfig*>(configuration()), 
                              parent, "Line Sampler Widget");
}

KisFilterConfiguration* KisLineSamplerFilter::configuration()
{   
    if(m_config == NULL)
    {
        m_config = new LineSamplerFilterConfig(this, 100, Qt::black);
    }
    return m_config;
};

KisFilterConfiguration* KisLineSamplerFilter::configuration(QWidget* nwidget)
{
    return configuration();
}

