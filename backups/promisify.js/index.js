'use strict';

module.exports = exports = function(fn) {
  return function() {
    var ctx = this;
    var args = arguments;
    return new Promise(function(resolve, reject) {
      var cb = function(err, data) {
        if (err) {
          return reject(err);
        }
        resolve(data);
      };
      [].push.call(args, cb);
      fn.apply(ctx, args);
    });
  };
};
