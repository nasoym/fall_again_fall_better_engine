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
		//TODO create specific
        Uuid() : 
			mUuid(boost::uuids::random_generator()())
			{ }

        ~Uuid(){}

		const std::string	toString() {
			return boost::lexical_cast<std::string>(mUuid);
		}

		//TODO compare operators
	private:
		boost::uuids::uuid mUuid;
};
//-------------------------------------
#endif
//-------------------------------------

