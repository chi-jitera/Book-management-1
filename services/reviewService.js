const Review = require('../models/Review');

/**
 * Retrieves all reviews for a specific book by its ID.
 * @param {string} bookId - The unique identifier for the book.
 * @returns {Promise<Array>} - Promise resolving to an array of reviews linked to the book.
 */
async function getReviewsByBookId(bookId) {
  // Fetch reviews where the 'book' field matches the provided bookId
  return await Review.find({ book: bookId });
}

module.exports = {
  getReviewsByBookId
};