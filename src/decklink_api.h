#if defined(__APPLE__)
#include "../interop/Mac/include/DeckLinkAPI.h"
#elif defined(__UNIX__)
#include "../interop/Linux/include/DeckLinkAPI.h"
#endif