set(HEADER
	"./Source/Public/Delegate.h"
)

set (SOURCE
	"./Source/Private/Main.cpp"
)

include_directories(Source/Public)

add_library(Delegate STATIC ${HEADER} ${SOURCE})
