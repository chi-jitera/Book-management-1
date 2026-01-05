const express = require('express');
const router = express.Router();
const bookController = require('../controllers/bookController');

// Create a book
router.post('/', bookController.createBook);

// Get all books
router.get('/', bookController.getAllBooks);

// Get a book by ID
router.get('/:id', bookController.getBookById);

// Search books
router.get('/search', bookController.searchBooks);

// Update book (full)
router.put('/:id', bookController.updateBookFull);

// Update book (partial)
router.patch('/:id', bookController.updateBookPartial);

// Delete book
router.delete('/:id', bookController.deleteBook);

module.exports = router;