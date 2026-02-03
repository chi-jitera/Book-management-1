const express = require('express');
const router = express.Router();
const readerController = require('../controllers/readerController');

// CRUD operations
router.post('/', readerController.createReader);
router.get('/', readerController.getAllReaders);
router.get('/:id', readerController.getReaderById);
router.put('/:id', readerController.updateReader);
router.patch('/:id', readerController.updateReader);
router.delete('/:id', readerController.deleteReader);

// Borrow a book
router.post('/:readerId/borrow', readerController.borrowBook);

// Return a book
router.post('/:readerId/return', readerController.returnBook);

module.exports = router;