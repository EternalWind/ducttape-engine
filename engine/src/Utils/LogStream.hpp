
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_UTILS_LOGSTREAM
#define DUCTTAPE_ENGINE_UTILS_LOGSTREAM

#include <Config.hpp>

#include <QString>

#include <ostream>
#include <memory>

namespace dt {

// forward declaration due to circular dependency
class Logger;

/**
  * A class for formatting log messages and writing them to the correct output stream.
  */
class DUCTTAPE_API LogStream {
public:
    
    typedef std::shared_ptr<LogStream> LogStreamSP;
    
    static QString COLOR_RED;       //!< ANSI color code for red
    static QString COLOR_GREEN;     //!< ANSI color code for green
    static QString COLOR_YELLOW;    //!< ANSI color code for yellow
    static QString COLOR_BLUE;      //!< ANSI color code for blue
    static QString COLOR_PURPLE;    //!< ANSI color code for purple
    static QString COLOR_CYAN;      //!< ANSI color code for cyan
    static QString COLOR_NONE;      //!< ANSI color code for no color (reset)

public:
    /**
      * Advanced constructor. Creates a LogStream with the given name.
      * @param name the name of the new LogStream
      */
    LogStream(const QString name);

    /**
      * Formats a log message, taking into account the name of the logger.
      * @param logger the Logger the message was sent from
      * @param msg the log message
      * @returns the formatted message
      * @see SetFormat()
      */
    QString formatMessage(Logger* logger, const QString msg);

    /**
      * Formats and outputs a log message to the output stream.
      * @see FormatMessage()
      * @see SetStream()
      * @param logger the Logger the message was sent from
      * @param msg the log message
      */
    void output(Logger* logger, const QString msg);
    
    /**
     * Formats and outputs a log message to the defaults output streams:
     * Warning, Error, Info and Debug.
     * @see SetStream()
     * @param logger the Logger the message was sent from
     * @param msg the log message
     */
    void defaultOutput(Logger* logger, const QString& msg);

    /**
      * Sets the output stream for this LogStream.
      * @param stream the new output stream
      */
    void setStream(std::ostream& stream);

    /**
      * Sets the name (level) for this LogStream.
      * @param name the new name
      */
    void setName(const QString name);

    /**
      * Sets the format which is used to format the messages before displaying.
      * %1$s = logger name, %2$s = stream name, %3$s = log message
      * @see sprintf
      * @param format the new format string
      */
    void setFormat(const QString format);

    /**
      * Returns the Logger's name.
      * @returns the Logger's name
      */
    const QString getName() const;

    /**
      * Sets whether messages should be written to this stream or not. Useful for disabling some streams, e.g. DEBUG, while keeping
      * more important streams enabled, e.g. ERROR.
      * @param disabled Whether the stream should be disabled or not.
      */
    void setDisabled(bool disabled);

    /**
      * Returns whether the stream is disabled.
      * @returns Whether the stream is disabled.
      */
    bool isDisabled() const;
private:
    std::ostream* mStream;  //!< the output stream
    QString mFormat;    //!< the message format
    QString mName;      //!< this LogStream's name, also called "log level"
    bool mDisabled;         //!< Whether this LogStream is disabled or not.
};

} // namespace dt

#endif
