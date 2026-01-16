const express = require('express');
const readerController = require('../controllers/readerController');

const router = express.Router();

router.post('/readers', readerController.createReader);
router.get('/readers', readerController.getAllReaders);
router.get('/readers/:id', readerController.getReaderById);
router.put('/readers/:id', readerController.updateReader);
router.delete('/readers/:id', readerController.deleteReader);

module.exports = router;