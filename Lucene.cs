public async Task LoadCache() 
{
    CacheLoaded = false;

    try
    {
        Directory.CreateDirectory(Root);

        if (Directory.Exists(StagingPath))
            Directory.Delete(StagingPath, true);

        using (var writer = CreateStagingWriter())
        {
            var items = await LoadApplicationData(); // DB / API / etc

            foreach (var app in items)
            {
                var doc = new Document
                {
                    new StringField("Id", app.Id.ToString(), Field.Store.YES),
                    new TextField("Name", app.Name ?? "", Field.Store.YES),
                    new TextField("Category", app.Category ?? "", Field.Store.YES)
                };

                writer.AddDocument(doc);
            }

            writer.Commit();
        }

        AtomicSwapIndexes();

        CacheLoaded = true;
        CacheLoadedAt = DateTime.UtcNow;
    }
    catch (Exception ex)
    {
        Log.Fatal(ex, "Lucene cache load failed");
        CacheLoaded = false;
    }
}
