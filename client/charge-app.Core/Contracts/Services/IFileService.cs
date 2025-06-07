namespace charge_app.Core.Contracts.Services;

public interface IFileService
{
    // read file
    T Read<T>(string folderPath, string fileName);

    // write file
    void Save<T>(string folderPath, string fileName, T content);

    void Delete(string folderPath, string fileName);
}
