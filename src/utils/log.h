#pragma once

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define info CROW_LOG_INFO << __FILENAME__ << ":" << __LINE__ << "> "
#define error CROW_LOG_ERROR << __FILENAME__ << ":" << __LINE__ << "> "
#define warning CROW_LOG_WARNING << __FILENAME__ << ":" << __LINE__ << "> "
