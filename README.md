Trading Messages Parser (C++)

This project implements a zero-copy, delimiter-based parser for trading messages format "tag=value|tag=value|...".

The parser is designed for high-performance, low-latency environments (e.g., trading systems).

Key Features :Zero-copy parsing, std::from_chars & std::string_view to avoid memory allocation and allow parsing messages directly from network buffers, Delimiter-based.
