const Book = require('../models/Book');
const connectDB = require('../config/db');

exports.createBook = async (data) => {
  await connectDB();
  if (data.publishedYear && data.publishedYear > new Date().getFullYear()) {
    const err = new Error('Published year cannot be in the future.');
    err.statusCode = 400;
    throw err;
  }
  const book = new Book(data);
  return await book.save();
};

exports.getBooks = async () => {
  await connectDB();
  return await Book.find({});
};

exports.getBookById = async (id) => {
  await connectDB();
  return await Book.findById(id);
};

exports.updateBook = async (id, data) => {
  await connectDB();
  if (data.publishedYear && data.publishedYear > new Date().getFullYear()) {
    const err = new Error('Published year cannot be in the future.');
    err.statusCode = 400;
    throw err;
  }
  return await Book.findByIdAndUpdate(id, data, { new: true, runValidators: true });
};

exports.deleteBook = async (id) => {
  await connectDB();
  return await Book.findByIdAndDelete(id);
};