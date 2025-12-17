const express = require('express');
const router = express.Router();
const bookController = require('../controllers/bookController');

router.get('/books', bookController.getAllBooks);
router.post('/books', bookController.createBook);
router.get('/books/:id', bookController.getBookById);
router.put('/books/:id', bookController.updateBook);
router.patch('/books/:id', bookController.patchBook);
router.delete('/books/:id', bookController.deleteBook);

module.exports = router;