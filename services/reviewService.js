const Review = require('../models/Review');

/**
 * Get all reviews for a specific book
 * @param {string} bookId
 * @returns {Promise<Array>} Array of Review documents
 */
const getReviewsByBookId = async (bookId) => {
    return await Review.find({ book: bookId });
};

module.exports = {
    getReviewsByBookId
};