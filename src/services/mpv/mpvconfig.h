#ifndef MPVCONFIG_H
#define MPVCONFIG_H

/***************************************************************************
 *   Copyright (C) 2007-2009 Sergio Pistone (sergio_pistone@yahoo.com.ar)  *
 *   Copyright (C) 2010-2015 Mladen Milinkovic <max@smoothware.net>        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../../config/appconfiggroup.h"

#include <KStandardDirs>

namespace SubtitleComposer {
class MPVConfig : public AppConfigGroup
{
	friend class MPVBackend;
	friend class MPVConfigWidget;

public:

	virtual AppConfigGroup * clone() const
	{
		return new MPVConfig(*this);
	}

	bool hasAudioOutput() const
	{
		return !option(keyAudioOutput()).isEmpty();
	}

	QString audioOutput() const
	{
		return option(keyAudioOutput());
	}

	void setAudioOutput(const QString &audioOutput)
	{
		setOption(keyAudioOutput(), audioOutput);
	}

	bool hasVideoOutput() const
	{
		return !option(keyVideoOutput()).isEmpty();
	}

	bool hasHwDecode() const
	{
		return !option(keyHwDecode()).isEmpty();
	}

	QString videoOutput() const
	{
		return option(keyVideoOutput());
	}

	QString hwDecode() const
	{
		return option(keyHwDecode());
	}

	void setVideoOutput(const QString &videoOutput)
	{
		setOption(keyVideoOutput(), videoOutput);
	}

	void setHwDecode(const QString &hwDecode)
	{
		setOption(keyHwDecode(), hwDecode);
	}

	bool hasCacheSize() const
	{
		return !option(keyCacheSize()).isEmpty();
	}

	int cacheSize() const
	{
		return optionAsInt(keyCacheSize());
	} // in kbytes

	void setCacheSize(int kbytes) { setOption(keyCacheSize(), kbytes < 0 ? "" : QString::number(kbytes)); }

	bool hasAudioChannels() const
	{
		return !option(keyAudioChannels()).isEmpty();
	}

	int audioChannels() const
	{
		return qMax(1, optionAsInt(keyAudioChannels()));
	}

	void setAudioChannels(int channels)
	{
		setOption(keyAudioChannels(), channels < 1 ? "" : QString::number(channels));
	}

	bool hasVolumeAmplification() const
	{
		return !option(keyVolumeAmplification()).isEmpty();
	}

	int volumeAmplification() const
	{
		const int value = optionAsInt(keyVolumeAmplification());
		return value <= 0 ? 100 : value;
	}

	void setVolumeAplification(int amplification)
	{
		setOption(keyVolumeAmplification(), amplification < 1 ? "" : QString::number(amplification));
	}

	bool volumeNormalization() const
	{
		return optionAsBool(keyVolumeNormalization());
	}

	void setVolumeNormalization(bool enabled)
	{
		setOption(keyVolumeNormalization(), enabled);
	}

	bool frameDropping() const
	{
		return optionAsBool(keyFrameDropping());
	}

	void setFrameDropping(bool frameDropping)
	{
		setOption(keyFrameDropping(), frameDropping);
	}

	bool hasAutoSyncFactor() const
	{
		return !option(keyAutoSyncFactor()).isEmpty();
	}

	int autoSyncFactor() const
	{
		return optionAsInt(keyAutoSyncFactor());
	}

	void setAutoSyncFactor(int factor)
	{
		setOption(keyAutoSyncFactor(), factor < 0 ? "" : QString::number(factor));
	}

	static const QString & keyCacheSize()
	{
		static const QString key("CacheSize");
		return key;
	}

	static const QString & keyAutoSyncFactor()
	{
		static const QString key("AutoSyncFactor");
		return key;
	}

	static const QString & keyVideoOutput()
	{
		static const QString key("VideoOutput");
		return key;
	}

	static const QString & keyHwDecode()
	{
		static const QString key("HWDecoding");
		return key;
	}

	static const QString & keyFrameDropping()
	{
		static const QString key("FrameDropping");
		return key;
	}

	static const QString & keyHardFrameDropping()
	{
		static const QString key("HardFrameDropping");
		return key;
	}

	static const QString & keyAudioOutput()
	{
		static const QString key("AudioOutput");
		return key;
	}

	static const QString & keyAudioChannels()
	{
		static const QString key("AudioChannels");
		return key;
	}

	static const QString & keyVolumeAmplification()
	{
		static const QString key("VolumeAmplification");
		return key;
	}

	static const QString & keyVolumeNormalization()
	{
		static const QString key("VolumeNormalization");
		return key;
	}

private:

	MPVConfig() : AppConfigGroup("MPV", defaults()) {}

	MPVConfig(const MPVConfig &config) : AppConfigGroup(config) {}

	static QMap<QString, QString> defaults()
	{
		QMap<QString, QString> defaults;

		defaults[keyCacheSize()] = "5120";      // in kbytes
		defaults[keyAutoSyncFactor()] = "";

		defaults[keyVideoOutput()] = "";
		defaults[keyHwDecode()] = "auto";
		defaults[keyFrameDropping()] = "false";

		defaults[keyAudioOutput()] = "";
		defaults[keyAudioChannels()] = "";
		defaults[keyVolumeAmplification()] = "110";
		defaults[keyVolumeNormalization()] = "false";

		return defaults;
	}
};
}

#endif
