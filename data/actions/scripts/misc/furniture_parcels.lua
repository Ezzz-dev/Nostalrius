local parcels = {
	[2775] = 2374,
	[2776] = 2378,
	[2777] = 2358,
	[2778] = 2382,
	[2779] = 2366,
	[2780] = 2418,
	[2781] = 2422,
	[2782] = 2319,
	[2783] = 2316,
	[2784] = 2315,
	[2785] = 2314,
	[2786] = 2346,
	[2787] = 2349,
	[2788] = 2351,
	[2789] = 2433,
	[2790] = 2441,
	[2791] = 2449,
	[2792] = 2524,
	[2793] = 2523,
	[2794] = 2483,
	[2795] = 2465,
	[2796] = 2976,
	[2797] = 2979,
	[2798] = 2934,
	[2799] = 3485,
	[2800] = 2998,
	[2801] = 2445,
	[2802] = 2025,
	[2803] = 2029,
	[2804] = 2030,
	[2805] = 2904,
	[2806] = 3510,
	[2807] = 2959,
	[2808] = 2963,
	[2809] = 2426,
	[2810] = 2352,
	[2811] = 2982,
	[2812] = 2986,
	[5086] = 5046,
	[5087] = 5055,
	[5088] = 5056,
}

function onUse(player, item, fromPosition, target, toPosition)
	local parcel = parcels[item:getId()]
	if not parcel then
		return false
	end
	
	if not item:getParent():isTile() then
		item:getPosition():sendMagicEffect(CONST_ME_POFF)
	elseif not Tile(fromPosition):getHouse() then
		item:getPosition():sendMagicEffect(CONST_ME_POFF)
	else
		item:transform(parcel)
		item:getPosition():sendMagicEffect(CONST_ME_POFF)
	end
	
	return true
end
