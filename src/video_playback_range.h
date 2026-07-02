// Copyright (c) 2026, forksama
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.

#pragma once

#include "time_range.h"

#include <algorithm>

enum class VideoPlaybackRange {
	Begin,
	End,
	Before,
	After
};

inline TimeRange GetVideoPlaybackRange(TimeRange primary_range, VideoPlaybackRange range) {
	constexpr int preview_ms = 500;

	switch (range) {
		case VideoPlaybackRange::Begin:
			return TimeRange(primary_range.begin(), std::min(primary_range.end(), primary_range.begin() + preview_ms));
		case VideoPlaybackRange::End:
			return TimeRange(std::max(primary_range.begin(), primary_range.end() - preview_ms), primary_range.end());
		case VideoPlaybackRange::Before:
			return TimeRange(std::max(0, primary_range.begin() - preview_ms), primary_range.begin());
		case VideoPlaybackRange::After:
			return TimeRange(primary_range.end(), primary_range.end() + preview_ms);
	}

	return primary_range;
}
