#pragma once
#ifndef DEVICEENCODINGCONTRACT_H
#define DEVICEENCODINGCONTRACT_H
#include <string>
#include "messageprocessors/messageencoder.h"
class EncodingModule
{
public:
    EncodingModule(const MessageEncoder&, const std::string&);

    /*!
     * \brief ���������� �������� ����������.
     */
    void setEncoderAlgorithm(const std::string algorithmName);
    /*!
     * \brief ���������������� �������� ���������� � ��������.
     */
    void registerEncoderAlgorithm(BaseEncoderExecutor* algorithm);

    std::string encode(const std::string&) const;
    std::string decode(const std::string&) const;

    

private:
    BaseEncoderExecutor* m_encoderAlgorithm;
    MessageEncoder m_encoder;
};

#endif // !DEVICEENCODINGCONTRACT_H
