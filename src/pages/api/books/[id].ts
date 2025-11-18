// src/pages/api/books/[id].ts

import type { NextApiRequest, NextApiResponse } from 'next';

// Dummy in-memory data store (replace with DB access layer)
let books: { id: string; [key: string]: any }[] = []; // Replace with proper DB/model in implementation

export default function handler(req: NextApiRequest, res: NextApiResponse) {
  const allowedMethods = ['DELETE', 'PATCH'];
  if (!allowedMethods.includes(req.method!)) {
    res.setHeader('Allow', allowedMethods);
    return res.status(405).json({ message: 'Method Not Allowed' });
  }

  // Extract and validate book id
  const { id } = req.query;
  if (!id || typeof id !== 'string') {
    return res.status(400).json({ message: 'Invalid or missing book ID.' });
  }

  // Remove book from store (replace with actual DB operation)
  const index = books.findIndex((book) => book.id === id);

  if (index === -1) {
    // Book not found
    return res.status(404).json({ message: 'Book not found.' });
  }

  // PATCH method: Partial update
  if (req.method === 'PATCH') {
    const updateData = req.body;
    if (!updateData || typeof updateData !== 'object') {
      return res.status(400).json({ message: 'Invalid update data.' });
    }
    // Validate publishedDate, if present
    if (updateData.publishedDate) {
      const today = new Date();
      const publishedDateObj = new Date(updateData.publishedDate);
      if (publishedDateObj > today) {
        return res.status(400).json({ message: 'publishedDate cannot be in the future.' });
      }
    }
    // Update only present fields
    Object.keys(updateData).forEach((key) => {
      books[index][key] = updateData[key];
    });
    // Respond with updated book
    return res.status(200).json(books[index]);
  }

  // DELETE method
  books.splice(index, 1);

  // Success response
  return res.status(200).json({ message: 'Book deleted successfully.' });
}