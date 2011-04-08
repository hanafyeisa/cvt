#ifndef CVT_XMLTEXT_H
#define CVT_XMLTEXT_H

#include <cvt/io/xml/XMLLeaf.h>

namespace cvt {
	class XMLText : public XMLLeaf {
		public:
			XMLText( const String& value );
			XMLText( const XMLText& other );
			XMLText& operator=( const XMLText& other );
			~XMLText();

	};

	inline XMLText::XMLText( const String& value ) : XMLLeaf( XML_NODE_TEXT, "", value )
	{
	}

	inline XMLText::XMLText( const XMLText& other ) : XMLLeaf( XML_NODE_TEXT, "", other._value )
	{
	}

	inline XMLText::~XMLText()
	{
	}

	inline XMLText& XMLText::operator=( const XMLText& other )
	{
		_name = "";
		_value = other._value;
		return *this;
	}
}

#endif
