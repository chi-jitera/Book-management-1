exports.patchBook = async (bookId, updateData) => {
    const book = await Book.findByIdAndUpdate(bookId, updateData, { new: true, runValidators: true });
    if (!book) throw new Error('Book not found');
    return book;
};