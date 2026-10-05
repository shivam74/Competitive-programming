export const createProduct = async (req, res) => {
  try {
    const { name, price, description, tags } = req.body;

    // 1. Validate and format tags
    let tagArray = [];
    if (tags) {
      // Split by comma, trim extra spaces, and filter out any empty strings
      tagArray = tags.split(',').map(tag => tag.trim()).filter(tag => tag !== "");
    }

    if (tagArray.length < 3) {
      return res.status(400).json({ error: "At least 3 tags are required" });
    }

    // 2. Generate a unique serial number (sNo)
    // Using Date.now() ensures it's always unique even if products are deleted
    const sNo = Date.now(); 

    // 3. Insert into the database (use insertOne instead of insert)
    const newProduct = {
      sNo,
      name,
      price: Number(price), // Ensure price is stored as a number
      description,
      tags: tagArray
    };

    const result = await collection.insertOne(newProduct);
    
    // Attach the generated MongoDB _id to our response object
    newProduct._id = result.insertedId;

    res.status(201).json(newProduct);
  } catch (error) {
    console.error("Error creating product:", error);
    res.status(500).json({ error: "Server error" });
  }
};


export const deleteProduct = async (req, res) => {
  try {
    const { id } = req.params;

    // Ensure we actually received an ID
    if (!id) {
       return res.status(400).json({ error: "Product ID required" });
    }

    // Delete the specific product by its ObjectId
    const result = await collection.deleteOne({ _id: new ObjectId(id) });

    // If no document was deleted, it means the product doesn't exist
    if (result.deletedCount === 0) {
      return res.status(404).json({ error: "Product not found" });
    }

    res.status(200).json({ message: "Product deleted successfully" });
  } catch (error) {
    console.error("Error deleting product:", error);
    res.status(500).json({ error: "Server error" });
  }
};