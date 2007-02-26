
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

#include "LineSamplerConfig.h"

LineSamplerFilterConfig::LineSamplerFilterConfig(QObject* parent, int numberOfLines, QColor color)
    : QObject(parent)
    , KisFilterConfiguration( "LineSampler", 1 )
    , m_numberOfLines(numberOfLines) 
    , m_color(color)
{ }

void LineSamplerFilterConfig::fromXML(const QString & s)
{
    KisFilterConfiguration::fromXML(s);
    m_numberOfLines = KisFilterConfiguration::getProperty("numberOfLines").asInt();
    m_color = KisFilterConfiguration::getProperty("color").asColor();
}

QString LineSamplerFilterConfig::toString()
{
    m_properties.clear();
    KisFilterConfiguration::setProperty("numberOfLines", m_numberOfLines);
    KisFilterConfiguration::setProperty("color", m_color);

    return KisFilterConfiguration::toString();
}

void LineSamplerFilterConfig::SetNumberOfLines(int val)
{
    if(m_numberOfLines != val)
    {
        m_numberOfLines = val;
        emit NumberOfLinesChanged(val);
    }
}

void LineSamplerFilterConfig::SetColor(const QColor & val)
{
    if(m_color != val)
    {
        m_color = val;
        emit ColorChanged(val);
    }
}


