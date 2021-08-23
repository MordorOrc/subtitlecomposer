/*
 * SPDX-FileCopyrightText: 2007-2009 Sergio Pistone <sergio_pistone@yahoo.com.ar>
 * SPDX-FileCopyrightText: 2010-2018 Mladen Milinkovic <max@smoothware.net>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef SCRIPTING_SUBTITLE_H
#define SCRIPTING_SUBTITLE_H

#include "scripting_subtitleline.h"
#include "core/subtitle.h"
#include "core/rangelist.h"

#include <QExplicitlySharedDataPointer>
#include <QObject>

namespace SubtitleComposer {
class Subtitle;

namespace Scripting {
class Subtitle : public QObject
{
	Q_OBJECT

public slots:
/// NOTE: target defaults to an invalid value, which means using and operation
/// defined default value, generally dependent on translationMode value.
	double framesPerSecond() const;
	void setFramesPerSecond(double framesPerSecond);

	bool isEmpty() const;
	int linesCount() const;
	int lastIndex() const;

	QObject * firstLine();
	QObject * lastLine();
	QObject * line(int index);

	void changeFramesPerSecond(double toFramesPerSecond, double fromFramesPerSecond = -1.0);

	SubtitleLine * insertNewLine(int index, bool timeAfter, int target = -1);
	void removeLine(int index, int target = -1);
	void removeLines(const QObject *ranges, int target = -1);

	void swapTexts(const QObject *ranges);

	void splitLines(const QObject *ranges);
	void joinLines(const QObject *ranges);

	void shiftLines(const QObject *ranges, int msecs);
	void adjustLines(const QObject *range, int firstTime, int lastTime);
	void sortLines(const QObject *range);

	void applyDurationLimits(const QObject *ranges, int minDuration, int maxDuration, bool canOverlap);
	void setMaximumDurations(const QObject *ranges);
	void setAutoDurations(const QObject *ranges, int msecsPerChar, int msecsPerWord, int msecsPerLine, bool canOverlap, int calculationTarget = -1);

	void fixOverlappingLines(const QObject *ranges, int minInterval = 100);

	void fixPunctuation(const QObject *ranges, bool spaces, bool quotes, bool englishI, bool ellipsis, int target = -1);

	void lowerCase(const QObject *ranges, int target = -1);
	void upperCase(const QObject *ranges, int target = -1);
	void titleCase(const QObject *ranges, bool lowerFirst, int target = -1);
	void sentenceCase(const QObject *ranges, bool lowerFirst, int target = -1);

	void breakLines(const QObject *ranges, int minLengthForLineBreak, int target = -1);
	void unbreakTexts(const QObject *ranges, int target = -1);
	void simplifyTextWhiteSpace(const QObject *ranges, int target = -1);

	void setMarked(const QObject *ranges, bool value);

	void clearErrors(const QObject *ranges, int errorFlags);

	void checkErrors(const QObject *ranges, int errorFlags);

	void recheckErrors(const QObject *ranges);

private:
	static SubtitleComposer::RangeList toRangesList(const QObject *object);

	friend class SubtitleModule;

	Subtitle(SubtitleComposer::Subtitle *backend, QObject *parent);

	QExplicitlySharedDataPointer<SubtitleComposer::Subtitle> m_backend;
};
}
}
#endif
