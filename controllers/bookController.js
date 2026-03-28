const bookService = require('../services/bookService');

exports.createBook = async (req, res) => {
  try {
    const book = await bookService.createBook(req.body);
    res.status(201).json(book);
  } catch (error) {
    res.status(error.statusCode || 400).json({ error: error.message });
  }
};

exports.getAllBooks = async (req, res) => {
  try {
    const books = await bookService.getBooks();
    res.json(books);
  } catch (error) {
    res.status(error.statusCode || 500).json({ error: error.message });
  }
};

exports.getBookById = async (req, res) => {
  try {
    const book = await bookService.getBookById(req.params.id);
    if (!book) return res.status(404).json({ error: 'Book not found' });
    res.json(book);
  } catch (error) {
    res.status(error.statusCode || 404).json({ error: error.message });
  }
};

// PATCH /:id (partial update)
exports.updateBookPartial = async (req, res) => {
  try {
    const book = await bookService.patchBook(req.params.id, req.body);
    res.json(book);
  } catch (error) {
    res.status(error.statusCode || (error.message === 'Book not found' ? 404 : 400)).json({ error: error.message });
  }
};

// PUT /:id (full update)
exports.updateBookFull = async (req, res) => {
  try {
    const book = await bookService.updateBook(req.params.id, req.body);
    if (!book) return res.status(404).json({ error: 'Book not found' });
    res.json(book);
  } catch (error) {
    res.status(error.statusCode || 400).json({ error: error.message });
  }
};

// GET /search
exports.searchBooks = async (req, res) => {
  res.status(501).json({ error: 'Not implemented' });
};

exports.deleteBook = async (req, res) => {
  try {
    const deleted = await bookService.deleteBook(req.params.id);
    if (!deleted) return res.status(404).json({ error: 'Book not found' });
    res.json({ message: 'Book deleted successfully' });
  } catch (error) {
    res.status(error.statusCode || 404).json({ error: error.message });
  }
};