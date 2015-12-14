#include "../../../inc/slib/ui/s_view.h"
#include "../../../inc/slib/ui/core.h"

SLIB_UI_NAMESPACE_BEGIN
SView::SView()
{
	m_flagNativeParent = sl_true;
}

sl_bool SView::isNativeParent()
{
	return m_flagNativeParent;
}

sl_bool SView::isNativeGroup()
{
	if (isGroup()) {
		if (m_flagNativeParent) {
			Ref<ViewInstance> instance = getViewInstance();
			if (instance.isNotNull()) {
				return sl_true;
			}
		}
	}
	return sl_false;
}

void SView::setNativeParent(sl_bool flag)
{
	m_flagNativeParent = flag;
}

void SView::removeAllChildren()
{
	if (isNativeGroup()) {
		if (!(UI::isUIThread())) {
			UI::runOnUIThread(SLIB_CALLBACK_WEAKREF(SView, removeAllChildren, this));
			return;
		}
		ListLocker< Ref<View> > children(m_children.duplicate());
		for (sl_size i = 0; i < children.getCount(); i++) {
			Ref<View> child = children[i];
			if (child.isNotNull()) {
				removeChild(child.get());
			}
		}
	} else {
		ListLocker< Ref<View> > children(m_children);
		for (sl_size i = 0; i < children.getCount(); i++) {
			children[i]->removeParent(this);
		}
		m_children.removeAll();
	}
}

void SView::removeChild(const Ref<View>& _view)
{
	Ref<View> view = _view;
	if (view.isNotNull()) {
		if (isNativeGroup()) {
			Ref<ViewInstance> instanceChild = view->getViewInstance();
			if (instanceChild.isNotNull()) {
				removeChildInstance(instanceChild.get());
			}
			view->detach();
		}
		view->removeParent(this);
		m_children.removeValue(view);
	}
}

void SView::addChild(const Ref<View>& _view)
{
	Ref<View> view = _view;
	if (view.isNull()) {
		return;
	}
	if (isNativeGroup()) {
		attachChild(view);
	}
	view->setParent(this);
	m_children.addIfNotExist(view);
}

void SView::onAttach()
{
	if (isNativeGroup()) {
		ListLocker< Ref<View> > children(m_children);
		for (sl_size i = 0; i < children.count(); i++) {
			Ref<View> child = children[i];
			if (child.isNotNull()) {
				attachChild(child);
			}
		}
	}
}

const List< Ref<View> >& SView::getChildren()
{
	return m_children;
}

SLIB_UI_NAMESPACE_END