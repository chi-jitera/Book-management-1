const express = require('express');
const router = express.Router();
const readerController = require('../controllers/readerController');

router.post('/readers', readerController.createReader);
router.get('/readers', readerController.getReaders);
router.get('/readers/:id', readerController.getReaderById);
router.put('/readers/:id', readerController.updateReader);
router.delete('/readers/:id', readerController.deleteReader);

module.exports = router;
