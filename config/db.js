const mongoose = require('mongoose');

let cached = global.mongooseCache || { conn: null, promise: null };
global.mongooseCache = cached;

const dbConnect = async (uri) => {
  if (cached.conn) return cached.conn;
  if (!cached.promise) {
    cached.promise = mongoose.connect(uri, {
      useNewUrlParser: true,
      useUnifiedTopology: true,
    }).then((mongooseInstance) => {
      return mongooseInstance;
    });
  }
  cached.conn = await cached.promise;
  return cached.conn;
};

module.exports = dbConnect;