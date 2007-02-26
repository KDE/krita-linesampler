
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

#pragma once

#include <qobject.h>
#include <kis_filter_configuration.h>
#include <qcolor.h>

class LineSamplerFilterConfig : public QObject, public KisFilterConfiguration
{
    Q_OBJECT;

public:
    LineSamplerFilterConfig(QObject* parent, int numberOfLines, QColor color);

    virtual void fromXML( const QString&  );
    virtual QString toString();
    
    int NumberOfLines() const { return m_numberOfLines; };
    QColor Color() const { return(m_color); }

public slots:
    void SetNumberOfLines(int val);
    void SetColor(const QColor & val);

signals:
    void NumberOfLinesChanged(int);
    void ColorChanged(const QColor &);

private:
    int m_numberOfLines;
    QColor m_color;
};

