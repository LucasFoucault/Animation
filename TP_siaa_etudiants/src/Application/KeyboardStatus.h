#ifndef _Application_KeyboardStatus_H
#define _Application_KeyboardStatus_H

namespace Application
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	KeyboardStatus
	///
	/// \brief	Class memorizing the keyboard status (pressed and released keys).
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	22/03/2016
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class KeyboardStatus
	{
	protected:
		::std::vector<bool> m_status ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	KeyboardStatus::KeyboardStatus()
		///
		/// \brief	Default constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	22/03/2016
		////////////////////////////////////////////////////////////////////////////////////////////////////
		KeyboardStatus()
			: m_status(256, false)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool KeyboardStatus::isPressed(unsigned char key) const
		///
		/// \brief	Query if 'key' is pressed.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	22/03/2016
		///
		/// \param	key	The key.
		///
		/// \return	true if pressed, false if not.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool isPressed(unsigned char key) const
		{
			return m_status[key] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void KeyboardStatus::press(unsigned char key)
		///
		/// \brief	Press the given key.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	22/03/2016
		///
		/// \param	key	The key.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void press(unsigned char key) 
		{
			m_status[key] = true ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void KeyboardStatus::release(unsigned char key)
		///
		/// \brief	Releases the given key.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	22/03/2016
		///
		/// \param	key	The key.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void release(unsigned char key)
		{
			m_status[key] = false ;
		}
	};
}

#endif