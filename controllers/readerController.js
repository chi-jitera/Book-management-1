const Reader = require('../models/Reader');
const Book = require('../models/Book');

exports.addReader = async (req, res) => {
    try {
        const reader = new Reader(req.body);
        await reader.save();
        res.status(201).json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

exports.getReaders = async (req, res) => {
    try {
        const readers = await Reader.find().populate('borrowedBooks');
        res.json(readers);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

exports.borrowBook = async (req, res) => {
    try {
        const reader = await Reader.findById(req.params.readerId);
        const book = await Book.findById(req.params.bookId);

        if (!reader || !book) {
            return res.status(404).json({ error: 'Reader or Book not found' });
        }

        reader.borrowedBooks.push(book._id);
        await reader.save();

        res.json(reader);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};