<changes><change><info>Ensure schema matches documented fields and maintains compatibility with update operations.</info><content>// /models/Book.js
const mongoose = require('mongoose');

const bookSchema = new mongoose.Schema({
  title: { type: String, required: true },
  author: String,
  publishedDate: Date,
  genre: String
});

module.exports = mongoose.model('Book', bookSchema);</content></change>
          </changes>