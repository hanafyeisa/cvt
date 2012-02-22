/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifdef CVTDELEGATE_H

/*
   Mediocre Delegate implementation:
   - needs heap memory
   - additional indirection
   + but readable code
 */

/* General delegate interface */
template<typename T0 TYPENAMELIST>
class DelegateImpl<T0 ( TYPELIST )>
{
	public:
		virtual ~DelegateImpl() {}
		virtual T0 invoke( TYPELIST ) const = 0;
		virtual DelegateImpl<T0 ( TYPELIST )>* clone() const = 0;
		virtual bool operator==( const DelegateImpl& dimp ) const = 0;
		virtual bool operator!=( const DelegateImpl& dimp ) const { return !( *this == dimp );}
};

/* Delegate implementation for pointer to member */
template<class T, typename T0 TYPENAMELIST >
class DelegateMember<T, T0 ( TYPELIST )> : public DelegateImpl<T0 ( TYPELIST )>
{
	typedef T0 (T::*MemberPtr)( TYPELIST );

	public:
		DelegateMember( T* obj, MemberPtr mptr ) : _obj( obj ), _mptr( mptr ) {}

		virtual T0 invoke( TYPEARGLIST ) const
		{
			return (_obj->*_mptr)( ARGLIST );
		}

		virtual DelegateImpl<T0 ( TYPELIST )>* clone() const
		{
			return new DelegateMember<T, T0 ( TYPELIST )>( _obj, _mptr );
		}

		virtual bool operator==( const DelegateImpl<T0 ( TYPELIST )>& dimp ) const
		{
			const DelegateMember<T, T0 ( TYPELIST )>* other = dynamic_cast<const DelegateMember<T, T0 ( TYPELIST )>*>( &dimp );
			if( !other )
				return false;
			return ( _obj == other->_obj && _mptr == other->_mptr );
		}

	private:
		T* _obj;
		MemberPtr _mptr;
};

/* Delegate implementation for pointer to const member */
template<class T, typename T0 TYPENAMELIST >
class DelegateMemberConst<T, T0 ( TYPELIST )> : public DelegateImpl<T0 ( TYPELIST )>
{
	typedef T0 (T::*MemberPtr)( TYPELIST ) const;

	public:
		DelegateMemberConst( T* obj, MemberPtr mptr ) : _obj( obj ), _mptr( mptr ) {}

		virtual T0 invoke( TYPEARGLIST ) const
		{
			return (_obj->*_mptr)( ARGLIST );
		}

		virtual DelegateImpl<T0 ( TYPELIST )>* clone() const
		{
			return new DelegateMemberConst<T, T0 ( TYPELIST )>( _obj, _mptr );
		}

		virtual bool operator==( const DelegateImpl<T0 ( TYPELIST )>& dimp ) const
		{
			const DelegateMemberConst<T, T0 ( TYPELIST )>* other = dynamic_cast<const DelegateMemberConst<T, T0 ( TYPELIST )>*>( &dimp );
			if( !other )
				return false;
			return ( _obj == other->_obj && _mptr == other->_mptr );
		}

	private:
		T* _obj;
		MemberPtr _mptr;
};

/* Delegate implementation for function pointers */
template<typename T0 TYPENAMELIST >
class DelegateFunction<T0 ( TYPELIST )> : public DelegateImpl<T0 ( TYPELIST )>
{
	typedef T0 (*FuncPtr)( TYPELIST );

	public:
		DelegateFunction( FuncPtr fptr ) : _fptr( fptr ) {}

		virtual T0 invoke( TYPEARGLIST ) const
		{
			return _fptr( ARGLIST );
		}

		virtual DelegateImpl<T0 ( TYPELIST )>* clone() const
		{
			return new DelegateFunction<T0 ( TYPELIST )>( _fptr );
		}

		virtual bool operator==( const DelegateImpl<T0 ( TYPELIST )>& dimp ) const
		{
			const DelegateFunction<T0 ( TYPELIST )>* other = dynamic_cast<const DelegateFunction<T0 ( TYPELIST )>*>( &dimp );
			if( !other )
				return false;
			return _fptr == other->_fptr;
		}
	private:
		FuncPtr _fptr;
};

/* The real delegate */
template<typename T0 TYPENAMELIST >
class Delegate<T0 ( TYPELIST )>
{
	public:
		template<class T>
			Delegate( T* t, T0 ( T::*ptr )( TYPELIST ) )
			{
				_impl = new DelegateMember<T, T0 ( TYPELIST )>( t, ptr );
			}

		template<class T>
			Delegate( T* t, T0 ( T::*ptr )( TYPELIST ) const )
			{
				_impl = new DelegateMemberConst<T, T0 ( TYPELIST )>( t, ptr );
			}

		Delegate( const Delegate<T0 ( TYPELIST )>& d )
		{
			_impl = d._impl->clone();
		}

		Delegate( T0 ( *func )( TYPELIST ) )
		{
			_impl = new DelegateFunction<T0 ( TYPELIST )>( func );
		}

		~Delegate()
		{
			delete _impl;
		}

		T0 operator()( TYPEARGLIST ) const
		{
			return _impl->invoke( ARGLIST );
		}

		bool operator==( const Delegate& other ) const
		{
			return *_impl ==  *( other._impl );
		}

		bool operator!=( const Delegate& other ) const
		{
			return *_impl !=  *( other._impl );
		}

	private:
		DelegateImpl<T0 ( TYPELIST )>* _impl;
};


#endif
