/******************************************************************************
 * This file is part of dOpenCL.
 * 
 * dOpenCL is an implementation of the OpenCL application programming
 * interface for distributed systems. See <http://dopencl.uni-muenster.de/>
 * for more information.
 * 
 * Developed by: Research Group Parallel and Distributed Systems
 *               Department of Mathematics and Computer Science
 *               University of Muenster, Germany
 *               <http://pvs.uni-muenster.de/>
 * 
 * Copyright (C) 2013  Philipp Kegel <philipp.kegel@uni-muenster.de>
 *
 * dOpenCL is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * dOpenCL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with dOpenCL. If not, see <http://www.gnu.org/licenses/>.
 * 
 * Permission to use dOpenCL for scientific, non-commercial work is
 * granted under the terms of the dOpenCL Academic License provided
 * appropriate credit is given. See the dOpenCL Academic License for
 * more details.
 * 
 * You should have received a copy of the dOpenCL Academic License
 * along with dOpenCL. If not, see <http://dopencl.uni-muenster.de/>.
 ******************************************************************************/

/**
 * \file Error.h
 *
 * \date 2011-02-06
 * \author Philipp Kegel
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <dcl/CLError.h>
#include <dcl/DCLException.h>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <exception>
#include <string>

namespace dclicd {

class Error: public std::exception {
public:
    Error(cl_int err, const char *what = nullptr) throw ();
    Error(cl_int err, const std::string& what) throw ();

    /*! \brief Creates an OpenCL error from a dOpenCL CL error.
     *
     *  \param err  a dOpenCL CL error
     */
    Error(const dcl::CLError& err) throw ();

    /*! \brief Creates an OpenCL error from a dOpenCL exception.
     *
     *  \param err  a dOpenCL exception
     */
    Error(const dcl::ConnectionException& err) throw ();
    Error(const dcl::IOException& err) throw ();
    Error(const dcl::ProtocolException& err) throw ();

    virtual ~Error() throw ();

    /*!	\brief Gets the error string associated with this exception.
     *
     *	\return a memory pointer to the error message string.
     */
    virtual const char * what() const throw ();

    /*!	\brief Gets the error code associated with this exception.
     *
     *	\return the error code
     */
    cl_int err() const throw ();

protected:
    cl_int _err;
    std::string _what;
};

} /* namespace dclicd */

#endif /* ERROR_H_ */
