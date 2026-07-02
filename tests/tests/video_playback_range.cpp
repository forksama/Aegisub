// Copyright (c) 2026, forksama
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.

#include <main.h>

#include "../../src/video_playback_range.h"

namespace {
void expect_range(TimeRange range, int begin, int end) {
	EXPECT_EQ(begin, range.begin());
	EXPECT_EQ(end, range.end());
}
}

TEST(video_playback_range, begin_uses_first_500ms_of_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 3100), VideoPlaybackRange::Begin), 2400, 2900);
}

TEST(video_playback_range, begin_clamps_to_short_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 2750), VideoPlaybackRange::Begin), 2400, 2750);
}

TEST(video_playback_range, end_uses_last_500ms_of_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 3100), VideoPlaybackRange::End), 2600, 3100);
}

TEST(video_playback_range, end_clamps_to_short_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 2750), VideoPlaybackRange::End), 2400, 2750);
}

TEST(video_playback_range, before_uses_500ms_before_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 3100), VideoPlaybackRange::Before), 1900, 2400);
}

TEST(video_playback_range, before_clamps_to_zero) {
	expect_range(GetVideoPlaybackRange(TimeRange(300, 900), VideoPlaybackRange::Before), 0, 300);
}

TEST(video_playback_range, after_uses_500ms_after_primary_selection) {
	expect_range(GetVideoPlaybackRange(TimeRange(2400, 3100), VideoPlaybackRange::After), 3100, 3600);
}
