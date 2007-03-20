
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

#include "LineSamplerWdg.h"

#include <qlayout.h>
#include <qslider.h>
#include <qspinbox.h>
#include <kcolorbutton.h>

#include "LineSamplerWdgBase.h"
#include "LineSamplerConfig.h"

LineSamplerWdg::LineSamplerWdg(LineSamplerFilterConfig* config,
                               QWidget * parent, const char * name)
    : KisFilterConfigWidget(parent, name)
    , m_config(config)
    , m_widget(NULL)
{
    QGridLayout *widgetLayout = new QGridLayout(this, 1, 1);
    m_widget = new LineSamplerWdgBase(this);
    widgetLayout->addWidget(m_widget, 0, 0);

    connect( m_widget->m_NumLinesSlider, SIGNAL( valueChanged ( int ) ), 
             m_config, SLOT(SetNumberOfLines(int)) );
    connect( m_widget->m_NumLinesSpinBox, SIGNAL( valueChanged ( int ) ), 
             m_config, SLOT(SetNumberOfLines(int)) );
    connect( m_widget->m_ColorButton, SIGNAL(changed(const QColor &)),
             m_config, SLOT(SetColor(const QColor &)) );
    
    connect( m_config, SIGNAL(NumberOfLinesChanged(int)), 
             m_widget->m_NumLinesSlider, SLOT(setValue(int)) );
    connect( m_config, SIGNAL(NumberOfLinesChanged(int)), 
             m_widget->m_NumLinesSpinBox, SLOT(setValue(int)) );
    connect( m_config, SIGNAL(NumberOfLinesChanged(int)), 
             SIGNAL(sigPleaseUpdatePreview()) );
    connect( m_config, SIGNAL(ColorChanged(const QColor &)),
             this, SLOT(SetColor(const QColor &)) );
    connect( m_config, SIGNAL(ColorChanged(const QColor &)),
             SIGNAL(sigPleaseUpdatePreview()) );
}

void LineSamplerWdg::setConfiguration(KisFilterConfiguration* config)
{
    kdDebug(41006) << "LineSamplerWdg::setConfiguration: called\n";

    m_widget->m_ColorButton->setColor( m_config->Color() );
    m_widget->m_NumLinesSlider->setValue( m_config->NumberOfLines() );
    m_widget->m_NumLinesSpinBox->setValue( m_config->NumberOfLines() );
}

void LineSamplerWdg::SetColor(const QColor & color)
{
    m_widget->m_ColorButton->setColor( color );
}

void LineSamplerWdg::showEvent ( QShowEvent * )
{
    setConfiguration(m_config);
}

#include "LineSamplerWdg.moc"
