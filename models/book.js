// Example Book model using Mongoose (for MongoDB). 
// Adjust to project ORM or database as needed.

const mongoose = require('mongoose');

const bookSchema = new mongoose.Schema({
  title: { type: String, required: true },
  author: { type: String, required: true },
  publishedYear: { type: Number, required: true }, // Correction: use publishedYear
  genre: { type: String, required: true },
  available: { type: Boolean, default: true } // New field for availability
  // ... add other fields as project requires.
});

const Book = mongoose.model('Book', bookSchema);

module.exports = Book;