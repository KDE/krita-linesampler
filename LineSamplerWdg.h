
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

// TODO: remove that
#define LCMS_HEADER <lcms.h>
// TODO: remove it !

#include <kis_filter_config_widget.h>

class LineSamplerFilterConfig;
class LineSamplerWdgBase;
class QShowEvent;

class LineSamplerWdg : public KisFilterConfigWidget
{
    Q_OBJECT;
    
public:
    LineSamplerWdg(LineSamplerFilterConfig* config, QWidget * parent, const char * name);
    virtual void setConfiguration(KisFilterConfiguration*);

public slots:
    void SetColor(const QColor &);

protected:
    virtual void showEvent ( QShowEvent * );

private:
    LineSamplerFilterConfig* m_config;
    LineSamplerWdgBase* m_widget;
};

