const express = require('express');
const readerBookController = require('../controllers/readerBookController');

const router = express.Router();

router.post('/reader-books', readerBookController.addReaderBook);
router.get('/reader-books/readers/:readerId', readerBookController.getBooksByReader);
router.get('/reader-books/books/:bookId', readerBookController.getReadersByBook);

module.exports = router;
