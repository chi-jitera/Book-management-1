const express = require('express');
const readerController = require('../controllers/readerController');

const router = express.Router();

router.post('/readers', readerController.addReader);
router.get('/readers', readerController.getReaders);
router.post('/readers/:readerId/borrow/:bookId', readerController.borrowBook);

module.exports = router;