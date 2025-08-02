#include "logic_layer/apicontroller.hpp"
#include "utils/logger.hpp"
#include "utils/exceptions.hpp"
#include <json/json.h>
#include <string>
#include <fstream>
#include <drogon/drogon.h>

using shenshang::utils::logger::Logger;
using shenshang::utils::exception::BadRequestException;
using shenshang::utils::exception::InternalErrorException;

void shenshang::api::FileUpload::handle(const drogon::HttpRequestPtr& req,
                               std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
    drogon::MultiPartParser parser;
    auto result = parser.parse(req);

    if (result != 0 || parser.getFiles().empty()) {
        return rep("文件解析失败或未收到文件", std::move(callback));
    }

    auto file = parser.getFiles()[0];

    // ✅ 保存文件（可指定路径或文件名）
    std::string savePath = "./uploads/" + file.getFileName();
    file.saveAs(savePath);

    Json::Value extra;
    extra["filename"] = file.getFileName();
    extra["size"] = (Json::UInt64)file.fileLength();
    extra["md5"] = file.getMd5();
    rep(true, "上传成功", extra, std::move(callback));
}