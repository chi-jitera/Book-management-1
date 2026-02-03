const Reader = require('../models/Reader');
const Book = require('../models/Book');
const connectDB = require('../config/db');

/**
 * Create a new reader
 */
exports.createReader = async (data) => {
  await connectDB();
  const reader = new Reader(data);
  return await reader.save();
};

/**
 * Get all readers
 */
exports.getAllReaders = async () => {
  await connectDB();
  return await Reader.find({});
};

/**
 * Get a reader by ID
 */
exports.getReaderById = async (id) => {
  await connectDB();
  return await Reader.findById(id).populate('borrowedBooks.book');
};

/**
 * Update a reader by ID
 */
exports.updateReader = async (id, data) => {
  await connectDB();
  return await Reader.findByIdAndUpdate(id, data, { new: true, runValidators: true });
};

/**
 * Delete a reader by ID
 */
exports.deleteReader = async (id) => {
  await connectDB();
  return await Reader.findByIdAndDelete(id);
};

/**
 * Borrow a book for a reader
 */
exports.borrowBook = async (readerId, { bookId, dueDate }) => {
  await connectDB();

  // Check if the book exists and is available
  const book = await Book.findById(bookId);
  if (!book) throw new Error('Book not found');
  if (!book.available) throw new Error('Book is not available');

  const reader = await Reader.findById(readerId);
  if (!reader) throw new Error('Reader not found');

  // Prevent borrowing if already borrowed this book and not returned
  const alreadyBorrowed = reader.borrowedBooks.find(
    b => b.book.toString() === bookId && b.status === 'borrowed'
  );
  if (alreadyBorrowed) throw new Error('Reader has already borrowed this book and not returned yet.');

  // Add to reader's borrowedBooks
  reader.borrowedBooks.push({
    book: bookId,
    borrowDate: new Date(),
    status: 'borrowed',
    dueDate: dueDate ? new Date(dueDate) : undefined,
  });

  // Mark book as unavailable
  book.available = false;

  await book.save();
  await reader.save();

  return await reader.populate('borrowedBooks.book');
};

/**
 * Return a borrowed book for a reader
 */
exports.returnBook = async (readerId, { bookId }) => {
  await connectDB();
  const reader = await Reader.findById(readerId);
  if (!reader) throw new Error('Reader not found');

  const borrowEntry = reader.borrowedBooks.find(
    b => b.book.toString() === bookId && b.status === 'borrowed'
  );
  if (!borrowEntry) throw new Error('No borrowed book entry found for this reader/book.');

  // Mark as returned
  borrowEntry.status = 'returned';
  borrowEntry.returnDate = new Date();

  // Make the book available
  const book = await Book.findById(bookId);
  if (book) {
    book.available = true;
    await book.save();
  }
  await reader.save();

  return await reader.populate('borrowedBooks.book');
};