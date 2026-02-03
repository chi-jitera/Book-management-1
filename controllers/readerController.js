const readerService = require('../services/readerService');

/**
 * Create a new reader.
 */
exports.createReader = async (req, res) => {
  try {
    const reader = await readerService.createReader(req.body);
    res.status(201).json(reader);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

/**
 * Get all readers.
 */
exports.getAllReaders = async (req, res) => {
  const readers = await readerService.getAllReaders();
  res.json(readers);
};

/**
 * Get a single reader by ID.
 */
exports.getReaderById = async (req, res) => {
  try {
    const reader = await readerService.getReaderById(req.params.id);
    if (!reader) {
      return res.status(404).json({ error: 'Reader not found' });
    }
    res.json(reader);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

/**
 * Update a reader by ID.
 */
exports.updateReader = async (req, res) => {
  try {
    const reader = await readerService.updateReader(req.params.id, req.body);
    if (!reader) {
      return res.status(404).json({ error: 'Reader not found' });
    }
    res.json(reader);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

/**
 * Delete a reader by ID.
 */
exports.deleteReader = async (req, res) => {
  try {
    const reader = await readerService.deleteReader(req.params.id);
    if (!reader) {
      return res.status(404).json({ error: 'Reader not found' });
    }
    res.json({ message: 'Reader deleted' });
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

/**
 * Borrow a book for a reader.
 */
exports.borrowBook = async (req, res) => {
  try {
    const reader = await readerService.borrowBook(req.params.readerId, req.body);
    res.json(reader);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

/**
 * Return a book for a reader.
 */
exports.returnBook = async (req, res) => {
  try {
    const reader = await readerService.returnBook(req.params.readerId, req.body);
    res.json(reader);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};