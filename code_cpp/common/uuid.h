//-------------------------------------
#ifndef _UUID_H
#define _UUID_H

#include <string>
#include <boost/lexical_cast.hpp>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

//-------------------------------------
class Uuid {
    public:
        Uuid() : 
			mUuid(boost::uuids::random_generator()())
			{ }

        ~Uuid(){}

		const std::string	toString() {
			return boost::lexical_cast<std::string>(mUuid);
		}

		void		fromString(std::string value){
			mUuid = boost::uuids::string_generator()(value);
		}

		bool		isEqual(std::string value) {
			if (toString().compare(value) == 0 ) {
				return true;
			}
			return false;	
		}

	private:
		boost::uuids::uuid mUuid;
};
//-------------------------------------
#endif
//-------------------------------------

