const readerBookService = require('../services/readerBookService');

exports.addReaderBook = async (req, res) => {
    try {
        const readerBook = await readerBookService.addReaderBook(req.body);
        res.status(201).json(readerBook);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.getBooksByReader = async (req, res) => {
    try {
        const books = await readerBookService.getBooksByReader(req.params.readerId);
        res.json(books);
    } catch (error) {
        res.status(404).json({ error: error.message });
    }
};

exports.getReadersByBook = async (req, res) => {
    try {
        const readers = await readerBookService.getReadersByBook(req.params.bookId);
        res.json(readers);
    } catch (error) {
        res.status(404).json({ error: error.message });
    }
};
