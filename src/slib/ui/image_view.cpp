/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "../../../inc/slib/ui/image_view.h"

namespace slib
{
	SLIB_DEFINE_OBJECT(ImageView, View)
	
	ImageView::ImageView()
	{
		SLIB_REFERABLE_CONSTRUCTOR
		
		setSavingCanvasState(sl_false);
		
		m_scaleMode = ScaleMode::Stretch;
		m_gravity = Alignment::MiddleCenter;
	}
	
	ImageView::~ImageView()
	{
	}

	Ref<ImageView> ImageView::create(sl_ui_len width, sl_ui_len height, const Ref<slib::Drawable> &drawable)
	{
		Ref<ImageView> ret = new ImageView;
		if (ret.isNotNull()) {
			ret->setSource(drawable, UIUpdateMode::Init);
			ret->setWidth(width, UIUpdateMode::Init);
			ret->setHeight(height, UIUpdateMode::Init);
			return ret;
		}
		return sl_null;
	}
	
	Ref<Drawable> ImageView::getSource()
	{
		return m_source;
	}
	
	void ImageView::setSource(const Ref<Drawable>& source, UIUpdateMode mode)
	{
		m_source = source;
		if (source.isNotNull()) {
			sl_real h = source->getDrawableHeight();
			if (h > 0.0000001) {
				setAspectRatio(source->getDrawableWidth() / h, mode);
			}
		}
		if (mode == UIUpdateMode::Redraw) {
			invalidate();
		}
	}
	
	ScaleMode ImageView::getScaleMode()
	{
		return m_scaleMode;
	}
	
	void ImageView::setScaleMode(ScaleMode scaleMode, UIUpdateMode updateMode)
	{
		m_scaleMode = scaleMode;
		if (updateMode == UIUpdateMode::Redraw) {
			invalidate();
		}
	}
	
	Alignment ImageView::getGravity()
	{
		return m_gravity;
	}
	
	void ImageView::setGravity(Alignment align, UIUpdateMode mode)
	{
		m_gravity = align;
		if (mode == UIUpdateMode::Redraw) {
			invalidate();
		}
	}
	
	void ImageView::onDraw(Canvas* canvas)
	{
		canvas->draw(getBoundsInnerPadding(), m_source, m_scaleMode, m_gravity);
	}
	
	void ImageView::onMeasureLayout(sl_bool flagHorizontal, sl_bool flagVertical)
	{
		if (!flagVertical && !flagHorizontal) {
			return;
		}
		Ref<Drawable> source = m_source;
		if (source.isNotNull()) {
			if (flagHorizontal) {
				setMeasuredWidth((sl_ui_len)(source->getDrawableWidth()));
			}
			if (flagVertical) {
				setMeasuredHeight((sl_ui_len)(source->getDrawableHeight()));
			}
		}
	}

}
