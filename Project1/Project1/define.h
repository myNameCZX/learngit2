#pragma once


#define SAFE_DELETE(e) { if (0 !=e) {delete e; e=0;} }