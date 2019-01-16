function onSay(player, words, param)
	if Game.getWorldType() == WORLD_TYPE_PVP_ENFORCED then
		player:showTextDialog(1998, "Your character has not murders history.", false)
		return false
	end
	
	local today = os.time()
	local skullTicks = player:getPlayerKillerEnd()
	local lastDay = 0
	local lastWeek = 0
	local lastMonth = 0
	local egibleMurders = 0
	local dayTimestamp = today - (24 * 60 * 60)
	local weekTimestamp = today - (7 * 24 * 60 * 60)
	local monthTimestamp = today - (30 * 24 * 60 * 60)
	
	local killsDayRedSkull = configManager.getNumber(configKeys.KILLS_DAY_RED_SKULL)
	local killsWeekRedSkull = configManager.getNumber(configKeys.KILLS_WEEK_RED_SKULL)
	local killsMonthRedSkull = configManager.getNumber(configKeys.KILLS_MONTH_RED_SKULL)
	
	local killsDayBanishment = configManager.getNumber(configKeys.KILLS_DAY_BANISHMENT)
	local killsWeekBanishment = configManager.getNumber(configKeys.KILLS_WEEK_BANISHMENT)
	local killsMonthBanishment = configManager.getNumber(configKeys.KILLS_MONTH_BANISHMENT)
	
	for _, timestamp in pairs(player:getMurderTimestamps()) do
		if timestamp > dayTimestamp then
			lastDay = lastDay + 1
		end
		
		if timestamp > weekTimestamp then
			lastWeek = lastWeek + 1
		end
		
		egibleMurders = lastMonth + 1
		
		if timestamp <= monthTimestamp then
			egibleMurders = lastMonth
		end
		
		lastMonth = egibleMurders
	end
	
	local message = ""
	message = message .. "Default murders\n"
	message = message .. "- Daily kills for red skull " .. killsDayRedSkull .. "\n"
	message = message .. "- Weekly kills for red skull " .. killsWeekRedSkull .. "\n"
	message = message .. "- Monthly kills for red skull " .. killsMonthRedSkull .. "\n"
	
	message = message .. "- Daily kills for banishment " .. killsDayBanishment .. "\n"
	message = message .. "- Weekly kills for banishment " .. killsWeekBanishment .. "\n"
	message = message .. "- Monthly kills for banishment " .. killsMonthBanishment .. "\n"
	
	message = message .. "\n"
	
	message = message .. "Last murders within 24 hours " .. lastDay .. "\n"
	message = message .. "Last murders within a week " .. lastDay .. "\n"
	message = message .. "Last murders within a month " .. lastDay .. "\n"
	
	message = message .. "\n"
	
	message = message .. "Players you may kill for a red skull:\n"
	message = message .. "- Within 24 hours " .. killsDayRedSkull - lastDay .. " murders.\n"
	message = message .. "- Within a week " .. killsWeekRedSkull - lastWeek .. " murders.\n"
	message = message .. "- Within a month " .. killsMonthRedSkull - lastDay .. " murders.\n"
		
	message = message .. "\n"
	
	message = message .. "Players you may kill for a banishment:\n"
	message = message .. "- Within 24 hours " .. killsDayBanishment - lastDay .. " murders.\n"
	message = message .. "- Within a week " .. killsWeekBanishment - lastWeek .. " murders.\n"
	message = message .. "- Within a month " .. killsMonthBanishment - lastDay .. " murders.\n"
			
	player:showTextDialog(1998, message, false)
	return false
end
