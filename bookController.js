exports.deleteBook = async (req, res) => {
    try {
        const result = await bookService.deleteBook(req.params.id);
        res.status(200).json(result);
    } catch (error) {
        if (error.message === 'Book not found') {
            res.status(404).json({ error: error.message });
        } else {
            res.status(500).json({ error: 'An error occurred while deleting the book.' });
        }
    }
};
