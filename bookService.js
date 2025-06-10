exports.deleteBook = async (bookId) => {
    try {
        const book = await Book.findByIdAndDelete(bookId);
        if (!book) throw new Error('Book not found');
        return { message: 'Book deleted successfully' };
    } catch (error) {
        console.error(`Error deleting book with ID ${bookId}:`, error);
        throw new Error('An error occurred while deleting the book.');
    }
};
