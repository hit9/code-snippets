/**
 * @overview  Stream based logging module for nodejs/iojs.
 * @author    hit9
 * @copyright MIT. (c) Chao Wang <hit9@icloud.com>
 */

const util = require('util');

// Global registry. {name: logger}
const registry = {};

// Levels, {name: level}.
const levels = {
  DEBUG   : 10,
  INFO    : 20,
  WARN    : 30,
  WARNING : 30,
  ERROR   : 40,
  CRITICAL: 50,
};

// LevelNames, {level: name}.
const levelNames = {
  10: 'DEBUG',
  20: 'INFO',
  30: 'WARN',
  40: 'ERROR',
  50: 'CRITICAL'
};

// Level comparation operators
const LEVEL_GT = 1;
const LEVEL_GE = 2;
const LEVEL_EQ = 3;
const LEVEL_LT = 4;
const LEVEL_LE = 5;

// util months
const months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep',
  'Oct', 'Nov', 'Dec'];

/**
 * Get logger from global registry, examples:
 *
 *   getLogger('foo') => Logger(name='foo')  // father
 *   getLogger('foo.bar') => Logger(name='foo.bar')  // child
 *
 * @param {String} name
 * @return {Logger}
 */
function getLogger(name) {
  var logger,
      _name,
      father;

  if (!(name in registry)) {
    // create a logger
    logger = new Logger(name);

    // try to find a father logger to propagate from
    for (_name in registry)
      if (name.indexOf(_name+'.') === 0)
        if (!father || (father.propagate
                        && father.name.length < _name.length))
          father = registry[_name];

    if (father)
      logger.propagateFrom(father);

    registry[name] = logger;
  }

  return registry[name];
}

/**
 * Util to format a string, examples:
 *
 *  format(1, 2, 3)  // '1 2 3'
 *  format('%s %d', 'val', 123)  // 'val 123'
 *  format('%(key)s', {key: 'val'})  // 'val'
 *  format('%%s', 'val')  // '%%s'
 *  format('%%(key)s', {key: 'val'})  // '%%(key)s'
 *
 * @param {String} fmt
 * @param {Mixed} args..
 */
const formatRegExp = /%%?(\(\w+\))?[sdj]/g;
function format(fmt) {
  var args = arguments,
    isKeyValFmt = false,
    isOriginFmt = false,
    index = 0, val;

  if (typeof fmt !== 'string')
    return util.format.apply(null, args);

  return fmt.replace(formatRegExp, function(match, idx) {
    if (typeof idx === 'undefined' && !isKeyValFmt) {
      isOriginFmt = true;
      return util.format(match, args[++index]);
    }

    if (typeof idx === 'string' && !isOriginFmt) {
      isKeyValFmt = true;

      if (match.slice(0, 2) === '%%' || args.length === 1)
        return match;

      val = args[1][idx.slice(1, -1)];

      if (typeof val === 'function')
        val = val();
      return util.format('%' + match.slice(-1), val);
    }

    throw new Error('invalid format');
  });
}

/**
 * Util to pad string.
 *
 * @param {Number} n
 * @return {String}
 */
function pad(n) {
  return n < 10 ? '0' + n.toString(10) : n.toString(10);
}


// Default formartter
var defaultFormatter =
  '%(litetime)s %(levelname)s %(name)s[%(pid)d]: %(message)s';

/**
 * LogRecord constructor.
 *
 *    name       logger name
 *    level      record level (number)
 *    levelName  record level (string)
 *    levelname  record level (string, lowercase)
 *    fmt        record formatter string
 *    args       record arguments
 *    message    record message (fmt % args)
 *    pid        process id
 *    asctime    human readable time string for current datetime,
 *               e.g. '2003-07-08 16:49:45,896'
 *    litetime   another lite human readable time string for current
 *               datetime, e.g. '26 Feb 16:19:34'
 *
 * @param {Mixed} args..
 */
function LogRecord(args) {
  this.name       = args.name;
  this.fmt        = args.fmt;
  this.args       = args.args;
  this.level      = args.level;
  this.levelName  = levelNames[this.level];
  this.levelname  = this.levelName.toLowerCase();
  this.pid        = process.pid;
  this.message    = format.apply(null, [this.fmt]
                                 .concat(this.args));
}

// '2003-07-08 16:49:45,896'
LogRecord.prototype.asctime = function() {
  var d = new Date();
  return util.format('%s-%s-%s %s:%s:%s,%s',
                     pad(d.getFullYear()),
                     pad(d.getMonth() + 1),
                     pad(d.getDate()),
                     pad(d.getHours()),
                     pad(d.getMinutes()),
                     pad(d.getSeconds()),
                     pad(d.getMilliseconds()));
};

// 26 Feb 16:19:34
LogRecord.prototype.litetime = function() {
  var d = new Date();
  var time = [pad(d.getHours()),
              pad(d.getMinutes()),
              pad(d.getSeconds())].join(':');
  return [d.getDate(), months[d.getMonth()], time].join(' ');
};

// Format a record with a formartter.
LogRecord.prototype.format = function(formatter) {
  if (typeof formatter === 'string')
    return format(formatter, this) + '\n';

  if (typeof formatter === 'function')
    return formatter(this) + '\n';

  throw new TypeError('formatter should be a string or function')
};

/**
 * Logger constructor
 *
 *   name         logger name (string)
 *   propagate    if this logger can be a `father` (default: true)
 *   rules        logger rules (object {name: rule})
 *
 * @param {String} name
 */
function Logger(name) {
  if (typeof name !== 'string')
    throw new TypeError('string required')

  this.name      = name;
  this.propagate = true;
  this.rules     = {};
  this.father    = null;
}

/**
 * @param {Boolean} propagate
 */
Logger.prototype.setPropagate = function(propagate) {
  this.propagate = !!propagate;
};

/**
 * Propagate from a father logger.
 *
 * @param {Logger} father
 * @return {Logger} this
 */
Logger.prototype.propagateFrom = function(father) {
  this.father = father;
  return this;
};

/**
 * Add a rule to this logger.
 *
 *   rule.name       rule name (required)
 *   rule.level      level to emit stream writing. (default: INFO)
 *   rule.stream     a writable stream to logging to (required).
 *   rule.formatter  a string formatter or a function.
 *   rule.levelCmp   level comparation operator
 *
 * @param {Object} rule
 * @return {Object} rule
 */
Logger.prototype.addRule = function(rule) {
  if (!('name' in rule))
    throw new Error('rule.name required');

  if (!(rule.stream && rule.stream.writable))
      throw new Error('invalid stream');

  rule.level = rule.level || levels.INFO;
  rule.formatter = rule.formatter || defaultFormatter;
  rule.levelCmp = rule.levelCmp || LEVEL_GE;
  return this.rules[rule.name] = rule;
};

Logger.prototype.removeRule = function(name) {
  return delete this.rules[name];
};

Logger.prototype.getRule = function(name) {
  return this.rules[name];
};

Logger.prototype.debug = function() {
  return this.log(levels.DEBUG, arguments);
};

Logger.prototype.info = function() {
  return this.log(levels.INFO, arguments);
};

Logger.prototype.warn = function() {
  return this.log(levels.WARN, arguments);
};
Logger.prototype.warning = Logger.prototype.warn;

Logger.prototype.error = function() {
  return this.log(levels.ERROR, arguments);
};

Logger.prototype.critical = function() {
  return this.log(levels.CRITICAL, arguments);
};

Logger.prototype.fatal = function() {
  return this.log(levels.CRITICAL, arguments) && process.exit(1);
};

/**
 * Logging formatter with args on `level`.
 *
 *   logger.log('say %(word)', {word: 'hi'})
 *
 * @param {Number} level
 * @param {Array} args
 */
Logger.prototype.log = function(level, args) {
  var record = new LogRecord({
    name: this.name,
    level: level,
    fmt: args[0],
    args: [].slice.apply(args, [1])
  });

  var rules = {};

  util._extend(rules, this.rules);

  if (this.father)
    util._extend(rules, this.father.rules);

  if (!Object.keys(rules)) {
    process.stderr.write(util.format("No rules was found for logger %j",
                                     this.name));
    return false;
  }

  for (var name in rules)
    this.doLogging(record, rules[name]);

  return true;
};

/**
 * Do logging by rule.
 *
 * @param {Record} record
 * @param {Object} rule
 */
Logger.prototype.doLogging = function(record, rule) {
  if (rule.levelCmp == LEVEL_GT && record.level <= rule.level)
    return;
  if (rule.levelCmp == LEVEL_GE && record.level < rule.level)
    return;
  if (rule.levelCmp == LEVEL_EQ && record.level != rule.level)
    return;
  if (rule.levelCmp == LEVEL_LT && record.level >= rule.level)
    return;
  if (rule.levelCmp == LEVEL_LE && record.level > rule.level)
    return;
  rule.stream.write(record.format(rule.formatter));
};

// exports
exports.get          = getLogger;
exports.levels       = levels;
exports.levelNames   = levelNames;
exports.DEBUG        = levels.DEBUG;
exports.INFO         = levels.INFO;
exports.WARN         = levels.WARN;
exports.WARNING      = levels.WARNING;
exports.ERROR        = levels.ERROR;
exports.CRITICAL     = levels.CRITICAL;
exports.LEVEL_GT     = LEVEL_GT;
exports.LEVEL_GE     = LEVEL_GE;
exports.LEVEL_EQ     = LEVEL_EQ;
exports.LEVEL_LT     = LEVEL_LT;
exports.LEVEL_LE     = LEVEL_LE;
