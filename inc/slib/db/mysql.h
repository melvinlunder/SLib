/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_DB_MYSQL
#define CHECKHEADER_SLIB_DB_MYSQL

#include "database.h"

#if defined(SLIB_PLATFORM_IS_DESKTOP)
#define SLIB_DATABASE_SUPPORT_MYSQL
#endif

#if defined(SLIB_DATABASE_SUPPORT_MYSQL)

namespace slib
{
	
	class SLIB_EXPORT MySQL_Param
	{
	public:
		String host;
		sl_uint32 port;
		String user;
		String password;
		String db;

		sl_bool flagAutoReconnect;
		sl_bool flagMultipleStatements;

	public:
		MySQL_Param();

		~MySQL_Param();

	};

	class SLIB_EXPORT MySQL_Database : public Database
	{
		SLIB_DECLARE_OBJECT

	protected:
		MySQL_Database();

		~MySQL_Database();
	
	public:
		static Ref<MySQL_Database> connect(const MySQL_Param& param);

		static Ref<MySQL_Database> connect(const MySQL_Param& param, String& outErrorMessage);
	
	public:
		virtual sl_bool ping() = 0;
	
	public:
		static void initThread();

	};

}

#endif

#endif
