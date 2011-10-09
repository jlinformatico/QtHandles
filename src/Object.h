/*

Copyright (C) 2011 Michael Goffioul.

This file is part of QtHandles.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QtHandles is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __QtHandles_Object__
#define __QtHandles_Object__ 1

#include <QObject>

#include <octave/oct.h>
#include <octave/graphics.h>

class QObject;
class QWidget;

//////////////////////////////////////////////////////////////////////////////

namespace QtHandles
{

//////////////////////////////////////////////////////////////////////////////

class Container;
class ObjectProxy;

class Object : public QObject
{
  Q_OBJECT

public:
  Object (const graphics_object& go, QObject* obj = 0);

  virtual ~Object (void);

  base_properties& properties (void)
    { return object ().get_properties (); }
  
  const base_properties& properties (void) const
    { return object ().get_properties (); }

  template <class T>
  typename T::properties& properties (void)
    {
      return dynamic_cast<typename T::properties&>
	(object ().get_properties ());
    }
  
  template <class T>
  const typename T::properties& properties (void) const
    {
      return dynamic_cast<const typename T::properties&>
	(object ().get_properties ());
    }

  graphics_object object (void) const;

  virtual QObject* qObject (void) { return m_qobject; }

  template <class T>
  T* qWidget (void) { return qobject_cast<T*>(qObject ()); }

  virtual Container* innerContainer (void) = 0;

  static Object* fromQObject (QObject* obj);

public slots:
  void slotUpdate (int pId);
  void slotFinalize (void);
  void slotRedraw (void);

  void objectDestroyed (QObject *obj = 0);

protected:
  static Object* parentObject (const graphics_object& go);
  void init (QObject* obj, bool callBase = false);

  virtual void update (int pId);
  virtual void finalize (void);
  virtual void redraw (void);

protected:
  graphics_handle m_handle;
  QObject* m_qobject;
};

//////////////////////////////////////////////////////////////////////////////

}; // namespace QtHandles

//////////////////////////////////////////////////////////////////////////////

#endif
