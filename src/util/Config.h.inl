// This file describes options available for program configuration
// Configuration is stored as a JSON file, and the file name can be passed as an argument for the executable
// If no configuration file is present, sane defaults will be loaded and saved on (normal) exit.

// Option definition format: OPT(type, name, defaultValue)
// Handy type aliases:
// Int - platform-dependent integer
// Dbl - double precision floating point
// Str - std::string
// IntVec - std::vector<Int>
// DblVec - std::vector<Dbl>
// StrVec - std::vector<Str>
// StrStrMap - std::map<Str, Str>
// StrIntMap - std::map<Str, Int>
// StrDblMap - std::map<Str, Dbl>

// (You must use map aliases because of the way macros work)

OPT(Int, windowWidth, 1280)
OPT(Int, windowHeight, 800)

