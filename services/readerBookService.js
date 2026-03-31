const ReaderBook = require('../models/ReaderBook');

exports.addReaderBook = async (readerBookData) => {
    const readerBook = new ReaderBook(readerBookData);
    return await readerBook.save();
};

exports.getBooksByReader = async (readerId) => {
    return await ReaderBook.find({ readerId }).populate('bookId');
};

exports.getReadersByBook = async (bookId) => {
    return await ReaderBook.find({ bookId }).populate('readerId');
};
