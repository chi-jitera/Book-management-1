// src/pages/api/books/[id].ts

import type { NextApiRequest, NextApiResponse } from 'next'

// In-memory store for demonstration purposes only
let books: any[] = [];

export default function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  const {
    query: { id },
    method,
  } = req;

  // NOTE: Placeholder - integrate with MongoDB for production
  if (method === 'DELETE') {
    const index = books.findIndex(book => book.id === id);
    if (index === -1) {
      return res.status(404).json({ error: 'Book not found.' });
    }
    books.splice(index, 1);
    return res.status(204).end();
  } else {
    return res.status(405).json({ error: 'Method Not Allowed' });
  }
}