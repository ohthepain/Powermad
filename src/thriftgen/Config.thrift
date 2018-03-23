namespace java DF.Config
namespace py DF.Config
namespace cpp DF.Config

typedef i64 Timestamp
typedef string AssetPath

// Compatability

const i32 SchemaVersion = 1
const i32 SchemaVersionMinCompatible = 1

const string DefaultMatch3ThemeId = "Default"
const string LevelEditorLevelCampaignId = "C001-Business"
const string LevelEditorBuildingId = "LevelEditor"

typedef string LocalizationID

struct Localization
{
	1: required LocalizationID localizationId
	10: required string localizationPath
}

typedef string LocalizationKey

struct LocalizedString
{
	1: required LocalizationKey key
	2: optional string value;
}

struct DateTimeUTC {
    1: required i64 epochSeconds
}

enum RaidBossObjectiveType
{
	FirstStrike,
	MostDamage,
	LastStrike,
	Participation,
	Rally
}

// Markets v2
enum MarketType
{
	Default
	BlackMarket
}

enum AffinityID
{
	Chocolate
	Blue
	Green
	Orange
	Pink
	Yellow
}

enum SpecialtyID
{
	Donut
	Sorbet
	Cake
	Cookie
	Pie
	Cannoli
}

enum LootItemType
{
    Nothing = -1
    Currency = 0
    Building = 1
}

enum EventPhase
{
	NonEvent = 0,
	Main = 1,
	Preview = 2,
	Recap = 4,
}

enum EventPhases
{
	PreviewMainRecap = 0,
	Main = 1,
	Preview = 2,
	PreviewMain = 3,
	Recap = 4,
	MainRecap = 5,
}

enum GuildJoinType
{
    AutoJoin    = 0,
    Request     = 1,
    InviteOnly  = 2,
}

enum GuildMemberType
{
    Leader = 0,
    CoLeader = 1,
    Member1 = 2,
    Member2 = 3,
    Member3 = 4,
}

enum GuildState
{
    Active  = 0,
    Deleted = 1,
}

enum GuildQuestRewardType
{
    AllMembers = 0
    Leader = 1
    Guild = 2
}

// OpenGachaCard is deprecated
enum MessageButtonAction
{
	Default,
	GoToBuildMenu,
	GoToKingdom,
	GoToGachaStore,
	GoToCurrencyStore,
	GoToIsland,
	GoToURL,
	CollectGiftMessage,
	CancelFriendRequest,
	AcceptFriendRequest,
	SpinGacha,
	GoToSocialMenu,
	OpenGachaCard,
	RunFTUE,
	OpenGachaOffer,
	GoToInbox,
	GoToEventMenu,
	GoToEventMenuOpenRewards,
	GoToEventMenuOpenHelp,
	GoToEventMenuOpenStore,
	GoToEventMenuOpenLeaderboard,
    GoToRewards,
    GoToHelp,
    GoToStore,
    GoToLeaderboard,
    GoToNextEvoEventLevel, //NOT implemented yet
    GoToGuildLeaderboard,
}

enum EventMenuWidgetType
{
    ButtonWidget = 0,
    LeaderboardWidget = 1,
    PlayButtonWidget = 2, //Deprecating this now, we can just use parenting with a combination of ButtonWidget and TimerWidget
    ImageWidget = 3,
    TextWidget = 4,
    NPCImageWidget = 5,
    CurrencyHudWidget = 6,
    TimerWidget = 7,
    FakeLeaderboardWidget = 8,
    GuildLeaderboardPositionWidget = 9,
}
struct Header
{
    1: required i32 schemaVersion
    2: required i32 configVersion
}

// Bundles

typedef string BundleID
// ConfigBundle is for bundle definitions in excel spreadsheet
struct ConfigBundle
{
    1: required BundleID bundleId
    2: required string path
    3: optional i32 priority
	10: optional bool noncompulsory //Not able to use optional here as it is a thrift reserve keyword
	11: optional list<BundleID> dependencies
}

struct BundleInfo
{
	1: required string path
	2: optional i32 size
	3: required string bundlemd5
	4: required string zipmd5
	5: optional string url // used by the s3rver
}

// Bundles are generated in the asset bundle build script and are added to the PartialConfig file
struct Bundle
{
    1: required BundleID bundleId
    11: optional list<BundleID> dependencies
    12: optional map<string, BundleInfo> bundleInfo
	15: optional bool noncompulsory
	16: optional i32 priority
}

struct BundleManifest
{
	1: required string baseUrl
	3: required map<BundleID,Bundle> bundles
	4: optional string gitCommit
}

// Currencies

typedef string CurrencyID
typedef string CurrencyTypeID

struct Currency
{
    1: required CurrencyID currencyId
	11: required LocalizedString newDisplay
    13: required AssetPath catalogImage
	21: optional CurrencyTypeID currencyTypeId
	30: optional BundleID bundleId
	40: optional AssetPath gachaRevealImage
	41: required i32 startingValue
	42: optional LocalizedString pluralDisplay
}

// Rarities

typedef i32 RarityID

struct Rarity
{
    1: required RarityID rarityId
    3: required i32 weight
	4: optional LocalizedString newDisplay
	10: required string cardImage
	11: required i32 minBusinessOrderSlots
	12: required i32 maxBusinessOrderSlots
	13: required list<i32> slotPrices

	20: optional string gearGachaCardFrontImage
	21: optional string gearGachaCardBackImage
	22: optional string businessGachaCardFrontImage
	23: optional string businessGachaCardBackImage
	24: optional AssetPath smallCardBackground
	25: optional AssetPath gachaRibbon
	26: optional string gachaCounter
	27: optional AssetPath starBackground

	30: optional AssetPath detailGachaGearCardImage
	31: optional AssetPath detailGachaBusinessCardImage

	32: optional AssetPath buildMenuCardImageLocked
	33: optional AssetPath buildMenuCardImageUnlocked
	34: optional AssetPath buildMenuCardImageFree
	35: optional string buildMenuCardEffectColor
	36: optional string buildMenuTextColor
	37: optional string buildMenuNpcBgColor
	38: optional AssetPath buildMenuBusinessCardImage

	// chef hats
	40: optional AssetPath buildMenuChefhatEmptyImage
	41: optional AssetPath gachaChefhatEmptyImage
	42: optional AssetPath businessOrderMenuChefhatEmptyImage

	50: optional AssetPath detailGachaDecoCardImage
}

typedef string ProductID

// Buildings

enum BuildingType
{
    Default
    Business
    Expansion
    Market
    Deco
    Blocker
}

typedef i32 EvolutionID
typedef string BuildingID
struct Building
{
    1: required BuildingID buildingId

    10: required BuildingType buildingType
    15: optional BundleID bundleId
    16: required i32 tileHeight
    17: optional InventoryTabID inventoryTabId
    18: optional LocalizedString newDisplay
    19: optional LocalizedString newDisplayPlural
    20: required i32 sizeX
    23: required i32 sizeY
    21: optional bool canRotate
    22: required RarityID rarityId
    24: required EvolutionID evolutionId

    32: optional i32 rankMin
    39: optional BuildingID nextEvolveBuildingId
    40: optional BuildingID baseEvolveBuildingId
    41: required i32 sellPrice (deprecated="true")
    42: required CurrencyID sellCurrencyId (deprecated="true")
    45: optional list<i32> sellPrices
    46: optional list<CurrencyID> sellCurrencyIds

    53: required CurrencyID costCurrencyId
    54: required i32 cost // FIXME DEPRECATED. DO NOT REMOVE YET.
    55: required double costGrowthFactor
    56: required i32 baseCost

	60: optional bool cannotMove

	71: optional LocalizedString newEvolveName
	72: optional LocalizedString fullDisplayName

    80: optional i32 realHeight
    100: optional string luaInterface
    101: optional MarketType marketType

	110: optional i32 showAsGachaOfferIndex //This is a new feature to upsell the buildings in build menu
    111: optional i32 placedScore

    113: optional bool fountain // true for a Business building type that is a key generator

    120: optional i32 populationPlacedScore
    121: required bool hiddenFromBuildMenu

    122: optional MessageButtonAction onOpenAction
    123: optional list<string> onOpenActionParameter
}

typedef i32 EntityID
typedef i32 Coordinate

struct StartingKingdomEntity
{
	1: required EntityID entityId
	2: required BuildingID buildingId
	3: required Coordinate x
	4: required Coordinate y
	5: optional bool rotated
}

typedef string PresetKingdomID
struct PresetKingdomEntity
{
	1: required PresetKingdomID presetKingdomId
	2: required EntityID entityId
	3: required BuildingID buildingId
	4: required Coordinate x
	5: required Coordinate y
	6: optional bool rotated
}

typedef string IslandID
typedef string IslandObjectID
typedef string ColorID

enum IslandObjectType
{
	Level,
	Cakebox,
	Object
}

struct Color
{
	1: optional ColorID colorId
	2: optional i32 red
	3: optional i32 green
	4: optional i32 blue
	5: optional i32 alpha
}

struct IslandSettings
{
	1: optional string islandBackLayerGroup
	2: optional string islandMiddleLayerGroup
}

// Deprecated
struct IslandObject
{
	1: optional IslandObjectID islandObjectId
	2: optional i32 x
	3: optional i32 y
	4: optional string image
	5: optional ColorID tintColorId
	10: optional string param
	13: optional IslandObjectType type
	14: optional string islandGroup
}

struct Island
{
	1: required IslandID islandId
    3: required i32 pageNum
	4: optional LocalizedString newDisplay
	10: optional IslandID nextIslandId
	20: required string eventId
	30: required string tmxFilename //Deprecated, please use island object list id
	60: required AssetPath islandImage
	70: optional string islandGroup
	80: optional i32 x
	81: optional i32 y
}

typedef string RecipeID

struct Recipe
{
    1: required RecipeID recipeId
    10: optional AssetPath catalogImage
    11: optional LocalizedString newDisplay
}

typedef string InventoryTabID

struct InventoryTab
{
    1: required i32 index
    2: required InventoryTabID inventoryTabId
    10: required AssetPath image
	20: required string selectionSound
	21: optional LocalizedString title
}

// Materials

typedef string MaterialID

struct Material
{
	1:	required MaterialID materialID
	11: optional RarityID rarityId
	12: optional RankID levelId
	14:	optional LocalizedString newDisplay
	20: optional list<MaterialID> materialIds
	21: optional list<i32> materialCounts
	40: optional CurrencyID craftCostCurrencyId
	41: optional i32 craftCost
}

typedef string EvolutionMaterialID

struct BusinessEvolution
{
	1: required EvolutionMaterialID evolutionMaterialId
	2: required list<MaterialID> gearList
	3: required list<i32> materialCounts
}

// Order list

typedef string BusinessOrderListID

struct BusinessOrderList
{
	1:	required BusinessOrderListID businessOrderListId
	5:	required list<BusinessOrderID> businessOrderIds
}

typedef string BusinessID

struct Business
{
    1: required BusinessID businessId
    2: required BuildingID buildingId
	11: optional EvolutionMaterialID evolutionMaterialId
	40: optional CurrencyID evolveCostCurrencyId
	41: optional i32 evolveCost
	50: optional string npcId
}

typedef string BusinessOrderID

struct BusinessOrder// deprecated
{
	1:  required BusinessOrderID orderId
    3:  optional i32 sortIndex
    12: required RecipeID recipeId
    21: required CurrencyID orderCostCurrencyId
    22: required i32 orderCost
    23: required i32 orderTimeBasis
    24: required CurrencyID earnedCurrencyId
    25: required i32 earned
	30: required CurrencyID rushCostCurrencyId
	31: required i32 rushCostBasis
	32: optional i32 palPointsProduced
	33: optional i32 rushBonusPalPoints
	34: optional i32 xpProduced
	35: optional i32 socialGoldCost
	36: optional i32 gemCost
	40: optional i32 guildMatePalPointsProduced
	41: optional i32 guildMatePalPointsRushBonus
	50: optional WeightedLootListID lootListId
}
struct NewBusinessOrder
{
    1: required BusinessOrderID orderId
    2: required BuildingID businessId
    3: required list<EventID> eventIds
    4: required EventPhases eventPhases

    10: optional i32 sortIndex
    12: optional RecipeID recipeId
    21: optional CurrencyID orderCostCurrencyId
    22: optional i32 orderCost
    23: required i32 orderTimeBasis
    24: required CurrencyID earnedCurrencyId
    25: required i32 earned
	32: optional i32 palPointsProduced
	33: optional i32 rushBonusPalPoints
	34: optional i32 xpProduced
	40: optional i32 guildMatePalPointsProduced
	41: optional i32 guildMatePalPointsRushBonus
	50: optional WeightedLootListID lootListId
}
// Triple Currency Order for little shop

typedef string CharacterID

typedef string DecoID

struct Deco
{
    1: required DecoID decoId

    10: required BuildingID buildingId

    20: required CurrencyID bonusCurrencyId (deprecated="true") // ready to be removed on at least build >= #1957
    21: required i32 tier1 (deprecated="true") // ready to be removed on at least build >= #1957
    22: required i32 tier1Bonus (deprecated="true") // ready to be removed on at least build >= #1957
    23: required i32 tier2 (deprecated="true") // ready to be removed on at least build >= #1957
    24: required i32 tier2Bonus (deprecated="true") // ready to be removed on at least build >= #1957
    25: required i32 tier3 (deprecated="true") // ready to be removed on at least build >= #1957
    26: required i32 tier3Bonus (deprecated="true") // ready to be removed on at least build >= #1957

    30: optional i32 roadEditorGroup

	50: optional bool isRiver
}

struct Blocker
{
	1: required BuildingID buildingId
	2: required CurrencyID removeCurrencyId (deprecated="true") // ready to be removed on at least build >= #1957
	3: required i32 removeCost (deprecated="true") // ready to be removed on at least build >= #1957
}

// Gacha.xlsx

typedef string WeightedLootListID

struct WeightedLoot
{
    1: required WeightedLootListID lootListId
    2: optional CurrencyID itemId
    3: required LootItemType itemType
    4: optional EventID eventId
    10: required i32 itemAmount
    20: required double probability
    21: optional double bonusProbability (deprecated="true")
    22: optional double bonusMultiplier (deprecated="true")
    30: optional double probabilityMultiplier
}

//////////////////////////////////////////// Start Gacha Configs

// Gacha groups (main categories)
typedef string GachaGroupID
struct GachaGroup   // deprecated, we use GachaOffer directly now
{
    1: required GachaGroupID gachaGroupId
    2: required i32 index
    10: required list<GachaOfferID> gachaOffers
    11: required string description

    12: optional LocalizedString newDisplay

	14: required AssetPath cardImage
	15: optional string badge
	16: required AssetPath overlayImage
	20: optional string bundleId
	21: optional LocalizedString newDescription

	30: required AssetPath detailCardBg9
	31: optional bool detailCardHaveRays
	32: required string detailCardBizAreaBg
	33: required string detailCardBizAreaTextBg

	40: optional LocalizedString badge2
	41: optional string badge2Sticker

	50: optional AssetPath moduleImage
	51: optional AssetPath moduleCakeboxImage
	52: optional BuildingID moduleRewardBuildingId
	53: optional AssetPath moduleRewardImage
	54: optional AssetPath detailCardFullscreenBg
	55: optional AssetPath detailCardFullscreenBgBottom
	56: optional LocalizedString cardCountTextSingular
	57: optional LocalizedString cardCountTextPlural
}

typedef string GachaBannerID
struct GachaBanner
{
    1: required GachaBannerID gachaBannerId
    2: required i32 order
    3: optional LocalizedString display

	4: required AssetPath image
	5: required bool enabled

	10: optional GachaGroupID targetGachaGroupId (deprecated="true")
	11: optional MessageButtonAction messageAction
	12: optional string messageActionParameter

	20: optional string bundleId

	21: optional GachaOfferID targetGachaOfferId

	30: optional list<EventID> eventIds
	31: optional EventPhases eventPhases
	32: optional i32 showRank
	33: optional i32 hideRank
}

// Gacha offers
typedef string GachaOfferID
struct GachaOffer
{
    1: required GachaOfferID gachaOfferId
    10: required CurrencyID costCurrencyId
    11: required i32 costAmount
    12: required list<GachaPackID> gachaPackIds
    13: required list<i32> gachaPackSpins
    14: required list<GachaOfferID> unlockGachaOfferIds // Reserved - step up
    15: required i32 maxSpins // Reserved - One time only and step up
    16: required i32 maxFreeSpinsPerDay
    17: required i32 freeSpinCooldown // Number of seconds needed to wait before spinning the gacha again
    18: optional LevelID requiredLevelId
	20: optional LevelDotID cakeboxLevelDotId
	30: optional AssetPath boxImage
    31: optional AssetPath openBoxImage
	40: optional string purchaseSound
	50: optional i32 notifyFreeSpinIndex
	51: optional EventLockID eventLockId
	52: optional bool doesNotRestock
    53: optional LocalizedString display
    54: optional LocalizedString description

    // new fields merged from GachaGroup
    55: optional i32 storeIndex

	56: optional LocalizedString badge
	57: optional LocalizedString badge2
	58: optional AssetPath badge2Sticker

	59: optional AssetPath storeCardImage
	60: optional AssetPath storeCakeboxImage
	61: optional BuildingID storeRewardBuildingId
	62: optional AssetPath storeRewardImage
	63: optional AssetPath detailCardFullscreenBg           	// deprecated
	64: optional AssetPath detailCardFullscreenBgBottom			// deprecated
	65: optional LocalizedString storeCardCountTextSingular
	66: optional LocalizedString storeCardCountTextPlural

	70: optional list<EventID> eventIds
	71: optional EventPhases eventPhases
	72: optional i32 showRank
	73: optional i32 hideRank

	74: optional string offerBackgroundImage
	75: optional string cardImage
	76: optional string productIcon
	77: optional string ribbonImage
	78: optional LocalizedString ribbonText

	80: optional list<BuildingID> showBuildingIds
	81: optional bool showTierInfo
	82: optional BuildingID tierYouGetBuildingId
	83: optional BuildingID tierTopRewardBuildingId
	84: optional LocalizedString tierYouGetText
	85: optional LocalizedString tierTopRewardText
	86: optional LocalizedString tierBannerText
	87: optional string tierBannerImage
	79: optional LocalizedString tierRarityText

	88: optional bool detailCardHaveRays
	89: optional i32 discountedPrice
	90: optional bool upsellInBuildMenu

	100: optional list<CurrencyID> floorClearRewardCurrencyIds //Used by displaying floor clear rewards
	101: optional list<i32> floorClearRewardCurrencyAmounts //Used by displaying floor clear rewards

	105: optional LocalizedString detailScreenHeader

	110: optional string eventStoreImage

	// IAP
	200: required IAPProductID iapProductId	// If exists and non-empty, this offer is IAP

	210: optional BundleID bundleId

	// New fields added on 2/12/2018 to support the new gacha detail screen.
    220: optional string gradientColor1
    221: optional string gradientColor2

    222: optional AssetPath baseTerrainImage // The base terrain needed for the building. If this is missing, we will not be showing the buildings at all.
    223: optional AssetPath featureImage // If this is defined, then we will not be showing the buildings at all
    300: optional i32 unlockRank
    301: optional i32 showGuildRank
    302: optional i32 hideGuildRank
    303: optional i32 unlockGuildRank
}

// Gacha packs
typedef string GachaPackID
struct GachaPack
{
    1: required GachaPackID gachaPackId
    10: required list<LootTableID> lootTableIds
    11: required list<i32> lootTableSpins
}

// Gacha loot tables
typedef string LootTableID
struct LootTable
{
    1: required LootTableID lootTableId
    10: required double weight
    11: required LootItemType itemType
    12: required list<string> itemGroupIds
    13: required i32 amount
}

// Gacha currency item groups
typedef string LootCurrencyGroupID
struct LootCurrencyGroup
{
    1: required LootCurrencyGroupID groupId
    10: required list<CurrencyID> currencyIds
}

// Gacha building item groups
typedef string LootBuildingGroupID
struct LootBuildingGroup
{
    1: required LootBuildingGroupID groupId
    10: required list<BuildingID> buildingIds
}

//////////////////////////////////////////// End Gacha Configs

typedef i32 RankID

typedef string ExpansionTypeID
struct ExpansionType {
    1: required ExpansionTypeID expansionTypeId

    //Cosmetic changes for expansions
    20: optional string spritesheet
    21: optional string imagePrefix
}

typedef string ExpansionID
struct Expansion
{
	1: required ExpansionID expansionId
	10: optional BuildingID blockerId (deprecated="true") // ready to be removed on at least build >= #1957
	11: optional BuildingID buildingId
	12: optional list<CurrencyID> costCurrencyIds
	13: optional list<i32> costCurrencyAmounts

	15: optional ExpansionTypeID expansionTypeId

	//Cosmetic changes for expansions
	20: optional string spritesheet (deprecated="true") // use expansionTypeId
	21: optional string imagePrefix (deprecated="true") // use expansionTypeId
}

struct Rank
{
    1: required RankID rankId
    10: required i32 xp
    11: required i32 maxFriends
    12: required i32 maxBuildings
	13: required i32 maxStamina
	//Max Likes Reward	Max Likes Reward Ids
	14: required i32 maxKingdomLikes
	15: required KingdomLikeGiftID maxKingdomLikesGiftId
	16: optional CurrencyID rankUpCurrencyRewardId
	17: optional i32 rankUpCurrencyRewardAmount
	18: optional i32 awardedStamina
	19: optional i32 xpNeeded
	30: optional string newDisplay
	40: optional i32 requiredPlacedBuildingScore
	50: optional list<BuildingID> unlockedBuildingIds
	51: optional list<i32> unlockedBuildingAmounts

	60: optional list<LootTableID> lootTableIds
	61: optional list<i32> lootTableSpins
}
typedef i32 GuildRankID
struct GuildRank
{
    1: required RankID rankId
    2: required i64 pointsForRank
    10: optional AssetPath guildHallImage
    12: optional i32 realHeight
}

typedef string BoostID

typedef string BoostTypeID

struct Boost
{
    1: required BoostID boostId
    11: required BoostTypeID boostTypeId
	12: optional string unlockLevelId
	13: optional i32 minRank
	14: optional string tutorialFlag
    31: optional string hudText

	33: optional LocalizedString newDisplay
	34: optional LocalizedString newDescription

    40: optional string enablePredicate
    41: optional string anim
    42: optional string blastUpgrade
    43: optional string conditional
    44: optional i32 priority
	45: optional string matrix
	46: optional bool needsPlacement
	47: optional string predicate
	48: optional string selectionPredicate
	49: optional list<CellTypeID> immuneCellTypes

	50: optional i32 order
	60: optional AssetPath sealImage
	61: optional AssetPath buttonImage
	64: optional AssetPath buttonSelectedImage

	62: optional bool useGetCurrencyDialog

	63: optional string animFileName
	65: optional string soundFile

	70: optional list<EventID> eventIds
	71: optional EventPhases eventPhases
}

typedef string EventLockID

struct EventLock
{
    1: required EventLockID eventLockId
    2: optional bool override
    3: optional bool enabled
    12: optional i32 minRank
    13: optional i32 maxRank
	20: required string startTime // Format is: MM/DD/YYYY hh:mm AM/PM (ex. 10/22/2015 10:00 AM). Gets parsed into the game as a long unix timestamp.
	21: required string endTime // Format is: MM/DD/YYYY hh:mm AM/PM
	22: optional i32 period // Minimum resolution is minutes.
	23: optional i32 duration // Minimum resolution is minutes.
	30: optional CurrencyID gateCurrencyId	// balance of this currency must be non-zero
	31: optional BuildingID requiredBaseBuildingId
}

// DEPRECATED - remove from configs once 0.1.5 is live
typedef string BuildMenuSpecialCardID
struct BuildMenuSpecialCard
{
    1: required BuildMenuSpecialCardID cardId
    2: required i32 order
    3: required string imageFile
	4: required LocalizedString caption
	5: optional EventLockID eventLockId
	6: optional string soundFile
	7: optional MessageButtonAction messageAction
	8: optional string messageActionParameter
	9: optional LevelID requiredLevelId
	10: optional bool enabled
	11: optional string bundleId

	12: optional string contentImageFile
	13: optional bool withSpinningRays
}

typedef string LevelDotID
struct LevelDot //Deprecated
{

	1: required LevelDotID levelDotId
	// Old
	2: optional AssetPath levelOpenImage
	3: optional AssetPath levelLockImage
	4: optional AssetPath level1StarImage
	5: optional AssetPath level2StarImage
	6: optional AssetPath level3StarImage
	7: optional AssetPath levelRankLockImage
	8: optional AssetPath levelFirstRankLockImage
	10: optional AssetPath levelFirstLockImage
	20: optional AssetPath levelCurrentLockImage
}

 //For cakeboxes, we are only using unlock and lock image
struct LevelDotV2
{
    1: required LevelDotID levelDotId
    // New
    100: required string unlockLevelImage
    101: required string lockLevelImage
    102: required string wonLevelImage
    103: required string currentLevelImage
    104: required string emptyStarImage
    105: required string fullStarImage

    //We are adding a hooks to run some action after we complete the level dot win animation or collected cakebox
    120: optional MessageButtonAction postLevelDotAction
    121: optional list<string> postLevelDotActionParameters
}

typedef string LevelID
typedef string VillainID
typedef string LevelName
// DEPRECATED
// DEPRECATED
// DEPRECATED
struct Level
{
    1: required LevelID levelId
    2: required LevelName levelName
    3: optional list<LevelID> levelRequirements
	4: optional string buildingId
    5: optional IslandID islandId
	6: optional i32 villainThrowLimit
    10: optional i32 levelNumber
    12: optional list<EventID> eventIds
    13: optional i32 rankMin
	// DEPRECATED: starScores are in the match-3 data
    22: optional list<i32> starScores
	24: optional bool tutorial
    30:	required WeightedLootListID oneStarRewardListId
    31:	required WeightedLootListID twoStarRewardListId
    32:	required WeightedLootListID threeStarRewardListId
    53: required i32 staminaCost
    60: required CurrencyID ticketBonusCurrencyId
    61: required i32 ticketBonus
    62: required list<ExpansionID> expansionRewardIds
    63: required list<i32> expansionRewardAmounts
    70: optional LevelDotID levelDotId
	80: required NpcID npcId
	81: optional string closedText
	82: optional string playText1Star
	83: optional string playText2Star
	84: optional string playText3Star
	85: optional string winText1Star
	86: optional string winText2Star
	87: optional string winText3Star
    88: optional string winText1StarReplay
    89: optional string winText2StarReplay
    90: optional string winText3StarReplay
	100: optional LocalizedString newDisplay
	// DEPRECATED - remove from configs once 0.1.5 is live
	101: optional LocalizedString startText0Star
	// DEPRECATED - remove from configs once 0.1.5 is live
	102: optional LocalizedString startText1Star
	// DEPRECATED - remove from configs once 0.1.5 is live
	103: optional LocalizedString startText2Star
	// DEPRECATED - remove from configs once 0.1.5 is live
	104: optional LocalizedString startText3Star
	// DEPRECATED - remove from configs once 0.1.5 is live
	105: optional LocalizedString successText1Star
	106: optional LocalizedString successText2Star
	107: optional LocalizedString successText3Star
    108: optional list<CurrencyID> firstTimeCurrencyRewardIds
    109: optional list<i32> firstTimeCurrencyRewardAmounts
    110: optional string icon
}

enum LevelType
{
	Normal = 0,
	Blitz = 1,
	Illegal = 2,
}

enum LevelParentType
{
	Default = 0,
	Business = 1,
	CastleEvent = 2,
	Campaign = 3,
    EvolutionEvent = 4,
}

enum LevelAvailability
{
	Default = 0, // Same as 'All' at the moment
	Sequential,
	All,
	Loop,
}

struct NewLevel
{
    1: required LevelID levelId
    2: required LevelName levelName
    3: optional list<LevelID> levelRequirements
	4: optional string buildingId
    5: optional IslandID islandId
	6: optional i32 villainThrowLimit
	7: optional LevelType levelType
    10: optional i32 levelNumber
    12: optional list<EventID> eventIds
    13: optional i32 rankMin
	14: optional list<EventID> newEventIds
	15: optional EventPhases eventPhases
	// DEPRECATED: starScores are in the match-3 data
    22: optional list<i32> starScores
	24: optional bool tutorial
    30:	required WeightedLootListID oneStarRewardListId
    31:	required WeightedLootListID twoStarRewardListId
    32:	required WeightedLootListID threeStarRewardListId
    53: required i32 staminaCost
    60: required CurrencyID ticketBonusCurrencyId
    61: required i32 ticketBonus
    62: required list<ExpansionID> expansionRewardIds
    63: required list<i32> expansionRewardAmounts
    70: optional LevelDotID levelDotId
	80: required NpcID npcId
	81: optional string closedText
	82: optional string playText1Star
	83: optional string playText2Star
	84: optional string playText3Star
	85: optional string winText1Star
	86: optional string winText2Star
	87: optional string winText3Star
    88: optional string winText1StarReplay
    89: optional string winText2StarReplay
    90: optional string winText3StarReplay
	100: optional LocalizedString newDisplay

	101: optional LocalizedString startText0Star (deprecated="true") // ready to be removed on at least 0.1.5 is live
	102: optional LocalizedString startText1Star (deprecated="true") // ready to be removed on at least 0.1.5 is live
	103: optional LocalizedString startText2Star (deprecated="true") // ready to be removed on at least 0.1.5 is live
	104: optional LocalizedString startText3Star (deprecated="true") // ready to be removed on at least 0.1.5 is live

	105: optional LocalizedString successText1Star (deprecated="true") // ready to be removed on at least build >= #1957
	106: optional LocalizedString successText2Star (deprecated="true") // ready to be removed on at least build >= #1957
	107: optional LocalizedString successText3Star (deprecated="true") // ready to be removed on at least build >= #1957

    108: optional list<CurrencyID> firstTimeCurrencyRewardIds
    109: optional list<i32> firstTimeCurrencyRewardAmounts
    110: optional string icon

    120: optional AssetPath backgroundImage
    121: optional AssetPath cloudImage1
    122: optional AssetPath cloudImage2
    123: optional AssetPath cloudImage3

    124: required LevelParentType parentType
    125: required string parentId // LevelCampaignID
    126: required list<CurrencyID> consolationPrizeCurrencyIds
    127: required list<i32> consolationPrizeCurrencyAmounts
}

struct MatchThreeData
{
	// Core Data
	1: required LevelName levelName
	2: required i32 numMoves	// Number of moves
	3: required list<i32> starScores	// Star required for the level

	4: required i32 numRows		// Size of the board in rows -- Seems to be deprecated. It is now calculated from cellart in GetNumRowsColumnsFromArt
	5: required i32 numColumns	// Size of the board in column  -- Seems to be deprecated. It is now calculated from cellart in GetNumRowsColumnsFromArt

	6: required i32 numColors	// Controls the number of donuts color in the board.
	7: optional i32 extraCount

	// Villain related
	20: optional VillainID villainId	// New villain id so that we can show other villain other than Dr. Celery
	21: optional i32 villainF	// Controls how frequently villains show up. 0 = no villains
	22: optional i32 villainN	// Controls how many vegetables villain shoots.
	23: optional i32 villainMechanicMin
	24: optional i32 villainMechanicMax
	25: optional i32 villainMargin
	26: optional i32 villainStartDelay
	27: optional string villainThrowZoneArt

	30: optional string extraLua  // Controls which tutorial to be shown
	31: optional list<i32> orderCount //Controls the orders required to be completed before winning level
	33: optional list<string> orderCountType //Controls the orders required to be completed before winning level
	32: optional string introuced

	// Not sure what all these are
	50: optional i32 hiddenCellDropsPermil
	51: optional i32 giftDropsPermil
	52: optional i32 uselessDropsPermil
	53: optional i32 carrotDropsPermil
	54: optional i32 eggplantDropsPermil
	55: optional i32 tomatoDropsPermil
	56: optional i32 eventPointDropsPermil

	//Actual board data
	71: optional string slimeArt
	72: optional string slimeString //Seems to be the same as slime string
	73: optional string conveyorart
	74: optional string bottomfenceart
	75: optional string rightfenceart
	76: optional string spriteart
	77: optional string freezeart
	78: optional string cellart

	80: optional i32 blueWeight
	81: optional i32 greenWeight
	82: optional i32 orangeWeight
	83: optional i32 chocoWeight
	84: optional i32 pinkWeight
	85: optional i32 clearWeight
	86: optional list<string> villainThrowTypes
	87: optional list<i32> villainThrowWeights
}

struct Villain
{
	1: required VillainID villainId
	2: required AssetPath villainImage
	3: optional list<AssetPath> villainThrowImage		// DEPRECATED -- still in use on at least build >= #1957
	4: optional string animationName
	5: optional list<string> villainThrowCells	// DEPRECATED -- still in use on at least build >= #1957
	6: optional string throwCellLoseText
	7: optional i32 mechanicMin	// DEPRECATED -- still in use on at least build >= #1957
	8: optional i32 mechanicMax	// DEPRECATED -- still in use on at least build >= #1957
}

typedef string LevelCampaignStyleID
struct LevelCampaignStyle
{
    1: required LevelCampaignStyleID levelCampaignStyleId
    2: required string campaignTMXFile
    3: required string characterNameBg
    4: required string myBalloonWithAvatar
    5: required string myBalloonWithoutAvatar // User below rank3 doesn't have avatar
    6: required string hudButtonImage
    7: required string topHudBannerBg
    8: required string campaignTitleBg9
    9: required string campaignTimerBg9
    10: required string leaderboardChestOnBanner
    11: required string infoButtonImage

    20: required string leaderboardTrophyImageOnHudButton
    21: required string eventStoreImageOnHudButton
    22: required string rewardChestTextBg

    //Campaign select page banners
    30: required string eventListBanner
    31: optional string eventListTitleTextColor
    32: optional string eventListStarTextColor

    // For events other than Castle event, you can supply the villain ID here to be read
    33: optional VillainID eventListvillainID

	// For Castle events the following are the texts on the HUDs
    40: optional LocalizedString topRewardText
    41: optional LocalizedString topPlayerText
    42: optional LocalizedString getMoreKeyText
    43: optional LocalizedString specialBoosterText
    44: optional LocalizedString eventStoreText

	// For some page, we will need a background to be displayed. For example, below the map layout and in recap screens.
    50: required AssetPath campaignBackground

	// Campaign map padding in tile, we need to enable padding so that the scrollview can bounce. So this variable will control how much we show in the tmx file
    60: optional i32 campaignMapPadding
}

typedef string LevelCampaignID
struct LevelCampaign
{
	1: required LevelCampaignID levelCampaignId
	2: required LevelParentType campaignType
	10: required i32 displayOrder
	11: required list<EventID> eventIds
	12: required EventPhases eventPhases
	13: required LevelAvailability availability
	14: required i32 showRank
	15: required i32 unlockRank
	16: required i32 hideRank

	17: required i32 numberOfFloors
	18: required i32 visibleFloors
	19: required bool hidden
	21: required bool hideWhenComplete
	22: required EventIslandID eventIslandId
    30: required LevelCampaignStyleID levelCampaignStyleID

	40: optional LocalizedString display

    50: optional BundleID bundleId

    60: required Match3ThemeId match3ThemeId
}

// Used for looking up all level ids for a particular campaign.
// Mutator script builds a lookup using this struct.
struct LevelCampaignLevelsList
{
	1: required LevelCampaignID levelCampaignId
	10: required list<LevelID> levelIds // Sorted by levelNumber in mutator script
}
struct BusinessLevelsList
{
	1: required LevelCampaignID levelCampaignId
	10: required list<LevelID> levelIds // Sorted by levelNumber in mutator script
}
struct CastleEventLevelsList
{
	1: required LevelCampaignID levelCampaignId
	10: required list<LevelID> levelIds // Sorted by levelNumber in mutator script
}
struct CampaignSettings
{
	1: required LevelCampaignID starterCampaignId
	2: required i32 starterCampaignLengthDays
	3: optional string starterCampaignWidgetPrefix
}

struct FTUESettings
{
    1: required string donutQuestId
    2: required string sundaeQuestId
    3: required string starterEventQuestId

    // New field introduce in 1.1.28, so that we can disable the FTUE across old and new separately due to changes in FTUE design
    10: required bool disableFtue

    // New fields introduce in 1.1.29
    20: required MainShopEntryID mainShopEntryId
    21: required BuildingID businessBuildingId
    22: required BuildingID decoBuildingId
    23: required QuestID evolveDonutStandQuestId
}

// StartingGameState
struct StartingGameState
{
    10: required i32 gems
    12: required i32 gold
    14: required i32 ticket
    15: optional PresetKingdomID kingdomVersion
	16: optional PresetKingdomID demoKingdomVersion
	20: optional double demoKingdomZoomDuration
	21: required list<BusinessID> freeRushOrderBusinessIds
	22: required list<i32> freeRushOrderAmounts
}

typedef string SocialUnlockRewardID

struct SocialUnlockReward
{
    1: required SocialUnlockRewardID rewardId
    2: required CurrencyID currencyId
    3: required i32 currencyAmount
}

struct BusinessMenuSettings
{
   1: optional GachaGroupID getGearGachaGroupId (deprecated="true") // ready to be removed on at least build >= #1957
    2: optional GachaGroupID getBusinessGachaGroupId (deprecated="true") // ready to be removed on at least build >= #1957
    3: optional GachaOfferID getGearGachaOfferId
    4: optional GachaOfferID getBusinessGachaOfferId
    5: optional AssetID getGearImage
    6: optional LocalizedString getGearText
}

struct Settings
{
	11: required i32 numBusinessMaterialSlots
	12: required string staminaCurrencyId
	13: required string goldCurrencyId
	14: required string xpStatId
	15: required string gemCurrencyId
	17: required i32 maxFriendInvites
	18: optional bool disableFtue
	19: optional bool disableBusinessIdleBullets
	20: required string palPointsCurrencyId
	21: optional i32 disableGoldStopgapMinRank (deprecated="true") // ready to be removed on at least build >= #1957

    26: required i32 maxAllowedClockChanges
    27: required i32 maxAllowedClockChangesPeriod
	28: required string refreshMarketOrdersCurrency (deprecated="true") // ready to be removed on at least build >= #1957
	29: required i32 refreshMarketOrdersCost (deprecated="true") // ready to be removed on at least build >= #1957
    30: required string ticketCurrencyId
	31: required RarityID maxRarity

    41: optional LevelDotID defaultRegularLevelDotID // deprecated -- still in use on at least build >= #1957
    42: optional LevelDotID defaultIngredientLevelDotID  (deprecated="true") // ready to be removed on at least build >= #1957
	43: optional LevelDotID defaultCakeBoxLevelDotID // deprecated -- still in use on at least build >= #1957
	44: required LevelDotID defaultLevelDotID

	60: optional list<CurrencyID> trackedCurrencies
	61: required i32 ticketsMinRank
	62: required list<string> defaultDimensions

	70: required i32 staminaRechargeRate
	80: required i32 orderBoardSize

	100: optional list<string> kingdomAmbientSounds
	101: optional list<string> kingdomAmbientMusic

	110: optional list<i32> localNotificationTimeSlots

	120: optional i32 dailyDecoBonusNotificationHour (deprecated="true") // ready to be removed on at least build >= #1957
	121: optional i32 dailyDecoBonusNotificationRepeatDays (deprecated="true") // ready to be removed on at least build >= #1957
	122: optional i32 socialMaxInactiveMinutes
	123: optional i32 pollIntervalSeconds (deprecated="true") // ready to be removed on at least build >= #1957
	124: optional SocialUnlockRewardID socialUnlockRewardId

	130: optional i32 maxKingdomSizeX
	131: optional i32 maxKingdomSizeY

	140: required string privacyPolicyURL
	141: required string termsOfUseURL
	142: required string legalURL
	143: optional string iOSRateGameURL1
	144: optional string iOSRateGameURL2
	145: optional string androidRateGameURL1
	146: optional string androidRateGameURL2
	147: optional string feedbackURL
	148: optional string supportURL

	150: optional i32 analyticsSchemaId
	160: required i32 centerKingdomEntityId
	170: optional i32 watchAdCooldown

	180: optional string iOSReRateGameBuildNumber
	181: optional string androidReRateGameBuildNumber
	190: optional string gachaFtueGachaGroupId (deprecated="true")
	191: optional string gachaFtueRareGachaGroupId (deprecated="true") // ready to be removed on at least build >= #1957
	192: optional string recipeIslandFirstRareCakebox (deprecated="true")
	193: optional string gachaFtueGachaOfferId
	194: optional string gachaFtueRareGachaOfferId

	200: optional i32 socialMenuMinRank
	201: optional i32 gachaStoreMinRank

	202: optional LevelID gachaStorePopoverMinLevel
	203: optional i32 inboxPopoverMinRank

	210: optional i32 gachaBannerDuration
	211: optional string placedBuildingStatId

	212: optional AchievementID spendGemsFTUETriggerOnObjectiveId
	213: optional AchievementID lockLinearObjectiveProgressionUntilCompleteObjectiveId
	214: optional i32 playerDisplayMaxLength
	215: optional string playerDisplayAllowedCharacters

	220: optional bool autoPopulatePlayerName

	230: optional bool disableGuild

	240: optional string placedBusinessScoreStatId

	250: optional i32 earnedCurrencyBonus // bonus based on decorations and population (business score).

	260: optional LocalizedString keyGearGetMoreText

	261: optional bool disableEvolveBullet

	262: required StoreID generalStoreId

	263: optional list<NpcID> additionalNpcsWalkingOnKingdom
}

struct PollSettings
{
	10: required i32 kingomIntervalSeconds

	20: required i32 eventIntervalSeconds

	30: required i32 gachaIntervalSeconds

	40: required i32 guildIntervalSeconds
	41: required i32 guildChatIntervalSeconds

	50: required i32 inboxIntervalSeconds

        60: required i32 questMenuIntervalSeconds
}

struct HappinessSettings
{
    1: optional i32 happinessSuperHappy
    2: optional i32 happinessMediumHappy
    3: optional i32 happinessNormal
}

typedef string BlobID
struct LevelBlob
{
    1: required BlobID blobId
    2: required map<string, string> keyValuePairs
}

//This will be called during specific moment to modify the screen view stack, if valid mapping is found it will added to the screen stack and get send along with gacha or gems purchase.
struct ScreenNameMapping
{
	//Lua file name wil be checked on DoDialog and TransitionScreen, or you can define your own custom name for special case handling.
	2: required string luaFilenameOrCustomName
	3: required string analyticsScreenName
}

typedef string AvatarID
struct Avatar
{
    1: required AvatarID avatarId
    20: required NpcID npcId
	21: required string emotionId
	30: required i32 index

    41: optional string eventMapImage
}

// Analytics Event

typedef string AnalyticsEventID

struct AnalyticsEvent
{
	1: required AnalyticsEventID analyticsEventId
	2: required string category
	3: required string label
	4: required i32 value
	5: optional list<string> payload
}

typedef string AnalyticsDimensionID

struct AnalyticsDimension
{
	1:	required AnalyticsDimensionID analyticsDimensionId
	2: optional string shortName
	10:	required i32 googleDimensionIndex
	20: optional string pooleSchemaKey
}

struct AppBoyEvent
{
	1: required AnalyticsEventID analyticsEventId
}

struct ApsalarEvent
{
	1: required AnalyticsEventID analyticsEventId
}

//Template for popups in game
typedef string TemplateID
struct PopupTemplate
{
	1: required TemplateID templateId
	2: optional string background
	3: optional string overlay
	10: optional list<string> buttonImages
	4: optional list<string> buttonTexts
	5: optional list<MessageButtonAction> buttonActions
	6: optional list<string> buttonParameters
	7: optional string bundleId
	8: optional string avatarId

	// Configurable for inbox messages display
	20: optional bool inboxHideRewards
	21: optional AssetID inboxMessageIcon

	30: optional string luaFile //Since we are having multiple type of templates now, we will now read this field to load different lua file for different format

	31: optional bool showEventTimer

	40: optional string backgroundLandscape
	41: optional string overlayLandscape
}

// Admin messages - these go in the config rather than being sent
// TODO: figure out how to consume these messages and mark them as read
typedef string AdminMessageID

enum GiftMessageType
{
    Default
    CustomerService
    RushOrder
    DeliverOrder
    LikeBonus
    DecoBonus
    Guild
    Gift // an actual gift!
    AskForItems
}

enum PopupTemplateType
{
	Default
	CustomerService
	RushOrder
	DeliverOrder
	LikeBonus
	DecoBonus
	FriendRequest = 2000
}

struct DefaultTemplate
{
	1: required PopupTemplateType popupTemplateType
	2: required TemplateID templateId
}

struct MessageTemplateModifier
{
	1: required PopupMessageID popupMessageId
	10: required string nodeName
	11: required string fieldName
	12: required string value
}

//TODO Dreprecate AdminMessage in favor of AdminGiftMessage
struct AdminMessage
{
        1: required AdminMessageID adminMessageId
        2: optional i32 priority
        3: required EventLockID eventLockId // FIXME Not Needed
        5: required string title // FIXME - Will be LocalizedString
        6: required string body // FIXME - Will be LocalizedString
        10: optional bool openable // TODO - Find out how this is used
        11: optional string openTitle // FIXME - Replace with title (Localized string)
        12: optional string openBody // FIXME - Replace with body (Localized string)
        14: optional bool autoOpen // FIXME - Remove this - This will be used in popups instead.
        20: optional list<CurrencyID> giftCurrencyIds //FIXME Stop using this in s3rver
        21: optional list<i32> giftCurrencyAmounts //FIXME Stop using this in s3rver
        50: optional i32 startTimeOfDay //FIXME Not needed
        60: optional i32 duration//FIXME Not needed
        61: optional bool enabled//FIXME Not needed - Replaced by "disabled" which makes more sense
        62: optional i32 minRank // FIXME Not needed - Replaced by showRank / hideRank
        64: optional TemplateID templateId // This is needed, move over to AdminGiftMessage
        65: optional bool oneTimeOnly // FIXME Maybe we do not need it

        //FIXME Fields that follow were marked as 'Deprecated' however, I am not sure if they are used in the code.
        4: required string characterId //Deprecated
        13: optional string openCharacterImage //Deprecated
        15: optional string openBackground //Deprecated
        16: optional MessageButtonAction openButtonAction //Deprecated
        17: optional list<string> openButtonParameters //Deprecated
        18: optional string openOverlay //Deprecated
        19: optional string openButtonText //Deprecated
        30: optional GachaOfferID gachaOfferId //Deprecated
        40: optional BundleID bundleId //Deprecated
        63: optional GiftMessageType giftMessageType //Deprecated TODO I think this is still used
}

typedef string NpcID

struct Npc
{
	1: required NpcID npcId
    2: optional i32 eyesLidBodyOffsetX
    3: optional i32 eyesLidBodyOffsetY
    4: optional i32 eyesLidLargeOffsetX
    5: optional i32 eyesLidLargeOffsetY
	6: optional string name
	10: optional string kingdomAnimation
	11: optional string kingdomAnimationFile
	12: optional string kingdomAnimationFile2

	20: optional string bigImage
}

enum PurchasableOfferType
{
	Default
	Gacha
	Card
	LegacyStoreProduct
}

enum OfferType
{
	Default
	Gacha
	Card
	LegacyStoreProduct
}

struct PurchasableOffer
{
	10: required PurchasableOfferType offerType
	11: required string offerId
}

typedef string IAPProductID
struct IAPProduct
{
	1: required IAPProductID iapProductId

	10: required AppleProductID appleProductId
	11: required GoogleProductID googleProductId

	// offer lookup (populated by mutators)
	20: optional PurchasableOffer offer
}

typedef string CardOfferID

struct CardOffer
{
	1: required CardOfferID cardOfferId
	10: required CurrencyID currencyId // If a valid iapProductId is provided, this is ignored
	11: required i32 currencyCost

	20: required CardOfferID unlockCardOfferId // If purchased, which card offer it unlocks.
	22: required i32 maxInventory
	27: required bool doesNotRestock

	32: required LocalizedString name
	33: required LocalizedString description
	34: optional bool displayRewardsReceived // If true, display rewards received in a popup after purchase

    40: required i32 showRank
    41: required i32 hideRank
    42: required i32 unlockRank
    43: optional i32 showGuildRank
    44: optional i32 hideGuildRank
    45: optional i32 unlockGuildRank

	50: required LootItemType productType
	51: required string productId
	52: required i32 productAmount

	// IAP
	60: required IAPProductID iapProductId // If exists and non-empty, this offer is IAP

	// IAP Store layout fields
	70: optional string offerBackgroundImage
	71: optional string cardImage
	72: optional string productIcon
	73: optional string ribbonImage
	74: optional LocalizedString ribbonText
	75: optional LocalizedString titleText
	76: optional LocalizedString bodyText
}

typedef string StoreTabID
struct StoreTab
{
    1: required StoreTabID storeTabId
    2: required AssetPath image
	3: optional string selectionSound
	4: required LocalizedString title
}
const StoreTabID AllItemStoreTabId = "All"

typedef string StoreID
struct Store
{
	1: required StoreID storeId
	2: required list<CurrencyID> currencyIds
	3: optional string localizedDisplay
	4: optional bool oneItemPerLine
	14: required LocalizedString display

	10: required list<EventID> eventIds
	11: required EventPhases eventPhases
	12: required i32 showRank
	13: required i32 hideRank

	20: required i32 restockTimerMinutes
	21: required CurrencyID restockCurrencyId
	22: required i32 restockCurrencyAmount

	32: required LocalizedString unaffordableMessage
	33: optional LocalizedString outOfStockMessage

	// new fields to match GachaOffer, so stores can be shown on Main shop
    40: optional LocalizedString description
	41: optional AssetPath storeCardImage
	42: optional BundleID bundleId

	43: optional string buttonImage
	44: optional string awningImage

    45: optional list<StoreTabID> storeTabIds
}

struct StoreInventoryItem
{
	1: required StoreID storeId

	// deprecated pre-1.9.4, but needed as loc key
	// (TODO: change to optional and populate with mutator)
	2: required OfferType offerType

	3: required string offerId

	5: required list<EventID> eventIds
	6: required EventPhases eventPhases

	7: required i32 displayOrder

	8: required LocalizedString display

    9: optional StoreTabID storeTabId
}

typedef string StoreProductID
typedef string AppleProductID
typedef string GoogleProductID

enum StoreProductBillingType
{
    Vendor
    Currency
}

struct VendorProduct
{
    1: required StoreProductID storeProductId
    2: optional AppleProductID appleProductId
    3: optional GoogleProductID googleProductId
}

struct StoreProduct
{
    1: required StoreProductID storeProductId
    2: required LootItemType itemType
    3: required CurrencyID itemId
    4: required i32 amount
    6: required StoreProductBillingType billingType
    7: optional CurrencyID billingCurrencyId
    8: optional i32 billingPrice
    9: optional AssetPath icon
    10: optional i32 listOrder
	11: optional LocalizedString newDisplay
	20: optional BundleID bundleId
	30: optional string debugPrice
	31: required list<LootTableID> lootTableIds
	32: required list<i32> lootTableSpins
	40: optional LocalizedString details
	50: optional bool disabled
}

typedef string MarketOrderID

struct BuyItemOrder
{
    1: required MarketOrderID orderId
    2: required MarketType marketType
    3: required CurrencyID buyCurrencyId
    4: required i32 buyCurrencyAmount
    5: required CurrencyID priceCurrencyId
    6: required i32 price
    7: required EventLockID eventLockId
}

struct Market
{
    1: required MarketType marketTypeId
    2: optional i32 numberOfSlots
    3: optional i32 openForInSecs
}

// Achievements
typedef string AchievementID
typedef string AchievementGroupID

enum AchievementType
{
    Unknown
    Bomb
    ColumnBlaster
    RowBlaster
    Colorbomb
    ScreenBlasterAColorbomb
    DoubleBlasterAColorbomb
    C2BlastersAColorbomb
    ColorbombABlaster
    ColorbombARowBlasterAColumnBlaster
    RowBlasterABlaster
    ColumnBlasterABlaster
    C2Blasters
    C3Blasters
    C2LineBlasters
    C3LineBlasters
    C4LineBlasters
    C5LineBlasters
    C6LineBlasters
    C7LineBlasters
    C8LineBlasters
    C9LineBlasters
    C10LineBlasters
    C2Colorbombs
    PlaceDeco
    GetBusiness
    EvolveBusiness
    CollectDailyBonus
    FinishIsland
	PlaceOrder
	CollectOrder
	RushOrder
	PlaceBusiness
	Rank
	LikeKingdom
	PlaceSocialOrder
    	OpenGachaPack
	VisitKingdom
	FinishLevel
	MoveBusiness
	MoveDeco
	PlaceExpansion
	MoveExpansion
	CraftGear
	EquipGear
	UseLevelBox
	PlaceRoad
	PlaceDistinctDecos
}

const string DailyAchievementGroupId = "ACG_DailyAchievements"
const string ObjectiveAchievementGroupId = "ACG_Objectives"
const string OrderCollectAchievementGroupId = "ACG_OrderCollect"
const string BusinessExpanderAchievementGroupId = "ACG_BusinessExpander"
const string BusinessPlaceAchievementGroupId = "AGC_BusinessPlace"
const string DecoratorAchievementGroupId = "ACG_Decorator"

const string RoadDecoTypeName = "Transportation" // This is the name in InventoryTabId column in Building sheet

struct Achievement
{
    1: required AchievementID achievementId
	2: optional i32 minRank
    4: required AchievementType achievementType
    5: required i32 requiredAmount

	6: required LocalizedString newDisplay
	7: required LocalizedString newDescription

    10: optional string param

    20: optional list<CurrencyID> rewardCurrencyIds
    21: optional list<i32> rewardAmounts

    30: optional AchievementGroupID achievementGroupId
    31: optional i32 achievementGroupOrder
	32: optional string goButtonFtue

    40: optional AssetPath catalogImage

	50: optional bool forceShowMe
	51: optional bool noAutoPop
}

struct AchievementGroup
{
    1: required AchievementGroupID achievementGroupId
    20: optional EventLockID eventLockId
    30: optional i32 order
}

////////// NEW QUESTS //////////
/*

 Kingdom interaction quests:
    PlaceAnyBuilding - Used - Place 5 more Decorations
    PlaceSpecificBuilding - Used - Place 4 white fences
    PlaceSpecificBuildingWithRarity - Used - Place 1 Rare Business
    RotateAnyBuilding - Used - Rotate a Decoration, Rotate a Business
    MoveAnyBuilding - Used - Move a Decoration, move a Business

 Specific business quests:
    HarvestAnySpecificBusiness - Used - Collect 10 orders from the Donut business

 Level quests:
     AutoPlayAnyLevel - Used - Autoplay any level
     WinAnyLevel - Used - Win a Match 3 level
     WinSpecificLevel - Used - Win the Ice Pop Business Level
     WinAnyLevelThreeStars - Used - Get three stars on any level

  Match 3 in game
     MatchUseSpecificBooster - Used - Use a COLUMN BLASTER Booster

  Social
      SocialLikeKingdom - Used - Like 3 Kingdoms
      SocialVisitKingdom - Used - Visit 4 Kingdoms
 */
enum GoalType
{
    NoType = 0

    HarvestAnyBusiness
    HarvestSpecificBusiness

    EquipAnyGearOnAnyBusiness
    EquipAnyGearOnSpecificBusiness

    EvolveAnyBusiness
    EvolveSpecificBusiness

    PlaceAnyBuilding
    PlaceSpecificBuilding
    PlaceSpecificBuildingWithRarity

    RotateAnyBuilding
    MoveAnyBuilding

    AutoPlayAnyLevel

    WinAnyLevel               // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinLevelSpecificBusiness  // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinSpecificLevel          // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinAnyEventLevel          // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead

    SocialCompleteOrder = 17
    SocialLikeKingdom
    SocialPlaceOrderGuildMate
    SocialVisitKingdom

    EquipSpecificGearOnAnyBusiness
    EquipSpecificGearOnSpecificBusiness

    AutoPlayAnyEventLevel
    AutoPlaySpecificLevel

    JoinGuild

    MatchUseAnyBooster
    MatchUseSpecificBooster

    WinAnyLevelThreeStars              // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinLevelSpecificBusinessThreeStars // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinSpecificLevelThreeStars         // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead
    WinEventLevelThreeStars            // DO NOT REMOVE AND DO NOT USE - Use CompleteLevel instead

    // Match3
    MatchTiles = 32

    CompleteLevel // levelStars = 1, 2 or 3, levelId = null or Valid level id

    GachaSpin
}

typedef string QuestID
typedef string QuestNpcID
typedef string GoalID

struct Goal
{
    1: required GoalID goalId
    2: required LocalizedString displayText
    3: required QuestID questId

    5: required i32 orderIndex

    10: required GoalType goalType
    11: required i32 requiredProgress
    12: optional RankID requiredRank

    20: optional list<EventID> eventIds
    21: optional EventPhases eventPhases

    31: optional LevelID levelId
    32: optional BuildingType buildingType
    33: optional BuildingID buildingId
    34: optional RarityID rarity
    36: optional i32 evoLevel
    37: optional CurrencyID gearId
    38: optional BoostID boosterId
    39: optional list<CellTypeID> cellTypes
    40: optional i32 levelStars
    41: optional GachaOfferID offerId
}

struct QuestNpc
{
    1: required QuestNpcID questNpcId
    2: required NpcID npcId
    3: required LocalizedString questDescriptionText
    4: required LocalizedString questCompletedText
    5: optional AssetPath backgroundImage
}

struct BusinessQuestNpc
{
    1: required BuildingID baseBusinessId
    2: required QuestNpcID questNpcId
}

typedef string GuildQuestRewardID
struct GuildQuestReward
{
    1: required GuildQuestRewardID guildQuestRewardId

    10: required GuildQuestRewardType rewardRecipientType
    11: required list<LootTableID> lootTableIds
    12: required list<i32> lootTableSpins
}

struct Quest
{
    1: required QuestID questId
    2: required i32 orderIndex
    3: required QuestNpcID questNpcId
    4: optional list<EventID> eventIds
    5: optional EventPhases eventPhases
    6: optional bool disabled
    7: optional bool chained
    8: optional bool unlockedByBusiness
    9: optional bool periodic
    10: optional i32 showRank
    11: optional i32 hideRank
    12: optional i32 unlockRank
    13: optional i32 countPerPeriod
    14: optional i64 period
    15: optional QuestID unlockedByQuest
    16: required i32 xpReward
    17: optional list<CurrencyID> rewardCurrencyIds
    18: optional list<i32> rewardCurrencyAmounts
    19: required LocalizedString titleText
    20: required LocalizedString descriptionText
    21: optional BuildingID buildingId

    // Shared quests for guilds
    50: optional bool guildQuest
    51: optional i32 showGuildRank
    52: optional i32 hideGuildRank
    53: optional i32 unlockGuildRank
    54: optional GuildQuestRewardID guildQuestRewardId
    55: optional CurrencyID displayCurrencyId
    56: optional i32 displayCurrencyAmount

    200: optional map<GoalID, Goal> goals // Populated by mutator script
}

typedef i32 GoalDisplayTemplateID
struct GoalDisplayTemplate
{
	1: required GoalType goalType
	2: required LocalizedString text
	3: required LocalizedString textPlural
}

typedef i32 QuestDisplayTemplateID
struct QuestDisplayTemplate
{
	1: required GoalType goalType
	2: required QuestDisplayTemplateID templateId
	3: required LocalizedString titleText

}

struct QuestSettings
{
	2: required i32 refreshPeriodSeconds
	10: required i32 maxAllowedHarvests
	11: required i32 maxAllowedHarvestTimeSeconds
	12: required bool generatedQuestsEnabled
}

struct QuestRankSettings
{
    1: required RankID rankId
    2: required i32 xpToGenerate
    3: required i32 numberOfSlots
    10: required i32 harvestSpecificBusiness
    12: required i32 completeLevel
    13: required i32 autoPlaySpecificLevel
    14: required i32 socialLikeKingdom
    15: required i32 socialVisitKingdom
    16: required i32 socialPlaceOrderGuildMate
    17: required i32 socialCompleteOrder
    18: required i32 matchTiles
    19: required i32 placeDeco
    20: required i32 equipAnyGearOnAnyBusiness
    21: required i32 equipSpecificGearOnSpecificBusiness
    40: required i32 harvestMinTimeSeconds
    41: required i32 harvestMaxTimeSeconds
    50: required i32 placeDecoMin
    51: required i32 placeDecoMax
    60: required i32 socialLikeMinProgress
    61: required i32 socialLikeMaxProgress
    70: required i32 socialVisitMinProgress
    71: required i32 socialVisitMaxProgress
    80: required i32 socialPlaceOrderMinProgress
    81: required i32 socialPlaceOrderMaxProgress
    90: required i32 socialCompleteOrderMinProgress
    91: required i32 socialCompleteOrderMaxProgress
    100: required string matchTilesCells
    110: required i32 matchTilesMinProgress
    111: required i32 matchTilesMaxProgress
}

struct BuildingTypeLocalization
{
	1: required BuildingType buildingType
	2: required LocalizedString buildingTypeNameSingular
	3: required LocalizedString buildingTypeNamePlural
}
////////// EOF NEW QUESTS //////////

enum ClientPlatform
{
    iOS
    Android
}

struct ForcedUpgrade
{
    1: required ClientPlatform clientPlatform

    10: required string minClientVersion
    11: required string minClientBuild

    20: required string title
    21: required string details
    22: required string buttonText

    30: required string url
}

typedef string ErrorId

struct ErrorMessage
{
    1: required ErrorId errorId
    2: required string details
}

struct StrangerSettings
{
    10: required i32 numberTotal
    11: required i32 eligibleLastActiveSeconds
    12: required i32 fakePlayerRankHigher
    13: required i32 fakePlayerRankLower
    14: optional i32 maxRankForHighRankStrangerList
    15: optional i32 fakeRankForHighRankStrangerList
    16: optional bool enableHighRankStrangerList
    17: optional bool enableLastActiveRankStrangerList
}

struct StrangerMatchSettings
{
    10: required i32 minRank
    11: required i32 maxRank
    12: required i32 playersPerBucket
    13: required i32 bucketsHigher
    14: required i32 bucketsLower
}

struct PlayerMatchRankSettings
{
    1: required i32 currentLowerRank
    2: required i32 currentUpperRank
    3: required i32 numRanksUnder
    4: required i32 numRanksOver
}

struct FakeStrangerDisplay
{
    10: required string display
}

typedef string GiftMessageRewardID

struct GiftMessageReward
{
    1: required GiftMessageRewardID giftMessageRewardId
    2: required LootItemType itemType
    3: required CurrencyID itemId
    4: required i32 itemAmount
}

typedef string KingdomLikeGiftID
struct KingdomLikeGift
{
    1: required KingdomLikeGiftID kingdomLikeGiftId
    2: required list<GiftMessageRewardID> giftMessageRewardIds
    3: required string giftTitle
    4: required string giftBody
}

struct PartialKingdomLikeGift
{
    1: required i32 partialLikeCount
    2: required KingdomLikeGiftID kingdomLikeGiftId
}

typedef string PushMessageID

struct PushMessage
{
    1: required PushMessageID pushMessageId
    2: optional string oldMessage
    3: required LocalizedString message
}

enum AdPlatform
{
	IOS = 1,
	Android
}

enum AdProviders
{
	AdColony = 1,
	UnityAds = 2,
	IronSource = 3
}

struct AdProvider
{
	1:	required AdPlatform adPlatform
	2:	required AdProviders adProvider
	3:	required string appId
	4:	optional list<string> customParameters //eg: zone ids for adcolony
	5:	optional i32 priority	//Lower number have a higher priority
}

struct RushCostByRemainingTime
{
    1: optional i32 minRemainingTimeInSecs
    2: optional i32 maxRemainingTimeInSecs
    3: optional i32 gemCost
}

// Leaderboard(s) and Event
typedef string LeaderboardID
typedef string LeaderboardLeagueID
typedef string LeaderboardRibbonID
typedef string LeaderboardTemplateID
typedef string EventID
typedef string RewardMessageID
typedef string AssetID
typedef string EventIslandID
typedef string EventHowToPlayID
typedef string EventMainMenuID

struct RewardMessage
{
	1: required RewardMessageID rewardMessageId
	2: optional string localizedTitle
	3: optional string localizedBody
	4: required LocalizedString title
	5: required LocalizedString body
	6: required i32 priority

	10: required TemplateID templateId //This is reading a PopupTemplate
}

struct Event
{
	1: required EventID eventId
	10: required DateTimeUTC previewStartTime
	11: required DateTimeUTC mainStartTime
	12: required DateTimeUTC mainEndTime
	13: required DateTimeUTC recapEndTime
	14: required i32 repeatSeconds
	15: required EventID parentEventId
}

typedef string CellInfoMapID
typedef string CellTypeID
struct CellInfo
{
	1: required CellInfoMapID CellInfoMapId
	2: required CellTypeID cellTypeId
	3: required string cellImagePath
	4: optional string specialAnimationPath
}

typedef string Match3ThemeId
struct MatchThreeCellDefinition
{
	1: required Match3ThemeId match3ThemeId // This id will be "Default" for the default cell definitions
	2: required CellTypeID cellTypeId
	3: required LocalizedString displayName
	10: optional AssetPath cellImagePath

	13: optional AffinityID affinityId
	14: optional SpecialtyID specialtyId

	// Blast animations
	50: optional string blastJsonFilename
	51: optional string blastAtlasFilename
	52: optional string blastAnimationName
}

typedef string BlasterTypeID

struct MatchThreeBlasterDefinition
{
	1: required Match3ThemeId match3ThemeId // This id will be "Default" for the default cell definitions
	2: optional BlasterTypeID blasterTypeId
	3: optional LocalizedString displayName
	4: optional string cellMatchCategory

	// Blast animations
	50: optional string blastJsonFilename
	51: optional string blastAtlasFilename
	52: optional string blastAnimationName
}

typedef string CastleActivityID

typedef string KeyCostPerLevelID

struct CastleActivity {
    1: required CastleActivityID activityId
	2: required list<EventID> eventIds
	3: required EventPhases eventPhases
	4: required CurrencyID keyCurrencyId

	10: required i32 showRank
	11: required i32 unlockRank
	12: required i32 hideRank

	20: optional string localizedDisplay
	21: required LocalizedString display

	30: required list<BundleID> bundleIds
    31: required EventIslandID eventIslandId

	32: required CurrencyID eventPointCurrencyId
	33: optional EventHowToPlayID eventHowToPlayId
	34: optional EventMainMenuID eventMainMenuId

	35: required i32 keyCost1 (deprecated="true") // ready to be removed on at least build >= #1957
	36: required i32 keyCost2 (deprecated="true") // ready to be removed on at least build >= #1957
	37: required i32 keyCost3 (deprecated="true") // ready to be removed on at least build >= #1957
	38: required i32 eventPointMultiplier1 (deprecated="true") // ready to be removed on at least build >= #1957
	39: required i32 eventPointMultiplier2 (deprecated="true") // ready to be removed on at least build >= #1957
	40: required i32 eventPointMultiplier3 (deprecated="true") // ready to be removed on at least build >= #1957

	41: required BuildingID eventBusinessBuildingId
	42: optional VillainID villainId

	43: optional GachaOfferID eventGachaOfferId

	61: required CurrencyID ticketCurrencyId
	62: optional GachaOfferID eventTicketGachaOfferId

	70: required LeaderboardID soloLeaderboardId
	71: required LeaderboardID globalLeaderboardId
	72: optional GuildLeaderboardID guildLeaderboardId

	80: optional PopupMessageID endEventSequenceTriggerOnPopupMessageId

	81: optional i32 levelPerFloor
	82: optional i32 maxUnlockedFloor
	85: optional CellInfoMapID cellInfoMapId

	90: optional CurrencyID upsellCurrencyId
	91: optional GachaOfferID upsellCurrencyOpenGachaOfferId
	92: optional LocalizedString upsellCurrencyNotEnoughText
	93: optional i32 autoPlayKeyCost (deprecated="true") // ready to be removed on at least build >= #1957
	94: optional i32 autoPlayEventPointMultiplier (deprecated="true") // ready to be removed on at least build >= #1957
	95: optional KeyCostPerLevelID keyCostPerLevelId
	96: required BuildingID fountainBuildingId
	97: required LocalizedString fountainNotificationText
	99: optional i32 businessCountEventPointMultiplier (deprecated="true") // ready to be removed on at least build >= #1957
	100: required PopupMessageID upsellKeyPopupMessageId
	101: optional StoreID eventStoreId

	// Controls when the event stamp change their states. Only affects UI display, so i'm setting this to only.
    110: optional i32 eventStampStateChangeMultiplier //Defaults to 5x

    200: optional bool disableAutoPlay
    201: optional bool hideEventPointsOnLevelDots

    210: optional list<EventMenuWidgetID> eventMainMenuWidgets //Deprecated on 2/6/2018
    //We will run through all the widget and use everything that fits this prefix, making this change because this will make it much easier and effcient to manage compared to a list in 210.
    211: optional string eventMainMenuWidgetPrefix

    220: optional ExpansionID expansionId
}

struct RaidBossActivity {
    1: required CastleActivityID activityId
	2: required list<EventID> eventIds
	3: required EventPhases eventPhases
	4: required CurrencyID keyCurrencyId

	10: required i32 showRank
	11: required i32 unlockRank
	12: required i32 hideRank

	21: required LocalizedString display

	30: optional list<BundleID> bundleIds
    31: optional EventIslandID eventIslandId

	32: optional CurrencyID eventPointCurrencyId
	33: optional EventHowToPlayID eventHowToPlayId
	34: optional EventMainMenuID eventMainMenuId

	41: optional BuildingID eventBusinessBuildingId
	43: optional GachaOfferID eventGachaOfferId

	50: optional list<i32> affinityBonus
	51: optional list<i32> specialtyBonus

	61: optional CurrencyID ticketCurrencyId
	62: optional GachaOfferID eventTicketGachaOfferId

	70: optional LeaderboardID soloLeaderboardId
	71: optional LeaderboardID globalLeaderboardId
	72: optional GuildLeaderboardID guildLeaderboardId

	85: optional CellInfoMapID cellInfoMapId

	90: optional CurrencyID upsellCurrencyId
	91: optional GachaOfferID upsellCurrencyOpenGachaOfferId
	92: optional LocalizedString upsellCurrencyNotEnoughText
	95: optional KeyCostPerLevelID keyCostPerLevelId
	96: optional BuildingID fountainBuildingId
	97: optional LocalizedString fountainNotificationText
	100: optional PopupMessageID upsellKeyPopupMessageId
	101: optional StoreID eventStoreId

	// Controls when the event stamp change their states. Only affects UI display, so i'm setting this to only.
    110: optional i32 eventStampStateChangeMultiplier //Defaults to 5x

    211: optional string eventMainMenuWidgetPrefix

    220: optional ExpansionID expansionId
}


struct KeyCostPerLevel
{
    1: required KeyCostPerLevelID keyCostPerLevelId
    2: required LevelID levelId
    3: required i32 keyCost1
    4: required i32 keyCost2
    5: required i32 keyCost3
    6: required i32 eventPointMultiplier1
    7: required i32 eventPointMultiplier2
    8: required i32 eventPointMultiplier3
    9: required i32 autoPlayKeyCost
    10: required i32 autoPlayEventPointMultiplier
    11: required i32 autoPlayTicketCost

	// New for blitz
	20: optional CurrencyID costCurrencyId1
	21: optional CurrencyID costCurrencyId2
	22: optional CurrencyID costCurrencyId3
}

struct EventIsland
{
	1: required EventIslandID eventIslandId
	2: required string filename
	3: required i32 x
	4: required i32 y
	5: required i32 sizeX
	6: required i32 sizeY
	7: required i32 realHeight
}

struct EventHowToPlay
{
	1: required EventHowToPlayID eventHowToPlayId
	2: required AssetPath backgroundImage
	3: required string templateFile
	4: required AssetPath titleBackgroundImage

	10: required string step1
	11: required AssetPath step1Icon
	12: required string step2
	13: required AssetPath step2Icon
	14: required string step3
	15: required AssetPath step3Icon
	16: required AssetPath stepBackgroundImage
	17: required AssetPath stepBurstImage
	18: required AssetPath businessBannerBackgroundBg9
	20: required string businessBannerText
	21: required string hintText

	22: optional string step1Ftue
	23: optional string step2Ftue
	24: optional string step3Ftue

	25: optional AssetPath titleIcon
}

struct EventMainMenu
{
	1: required EventMainMenuID eventMainMenuId
	2: required AssetPath floorBackgroundImage
	3: required AssetPath topImagePortrait
	4: required AssetPath bottomImagePortrait
	5: required AssetPath topImageLandscape
	6: required AssetPath bottomImageLandscape
	7: required AssetPath timerScale9Image
	8: required LocalizedString hint
	9: required LocalizedString getBusinessText1
	10: required LocalizedString getBusinessText2
	11: required AssetPath rankLockBackgroundImage

	12: required LocalizedString previewText1
	13: required LocalizedString previewText2
	14: required AssetPath previewImage (deprecated="true") // ready to be removed on at least build >= #1957

	15: required LocalizedString recapText
	16: optional LocalizedString recapTextNotParticipated
	
	20: required AssetPath rewardButtonImage
	21: required AssetPath floorRewardBg
	22: required AssetPath floorRewardChestClosed
	23: required AssetPath floorRewardChestOpen

	// This can any currency id, this will overwrite the event building upsell slot if this is defined this will be placed on top of 9:getBusinessText1 and 10:getBusinessText2
	30: optional AssetPath bottomNavBuildingImage
	31: optional AssetPath bottomNavLeaderboardImage

	40: optional bool hidePreviewPhaseGetNowButton

	50: optional AssetPath rankLockAndPreviewBackground
	51: optional AssetPath rankLockAndPreviewBackgroundLandscape
	52: optional AssetPath rankLockAndPreviewTimerBackground
	53: optional AssetPath rankLockAndPreviewTimerBackgroundLandscape
	54: optional AssetPath previewOverlay
	55: optional AssetPath previewOverlayLandscape
	56: optional AssetPath rankLockOverlay
	57: optional AssetPath rankLockOverlayLandscape
	58: optional AssetPath recapRibbonImage
	59: optional AssetPath recapTrophyTableImage
}

struct LeaderboardSettings {
    1: required i32 leaderboardGracePeriodSeconds
    2: required i32 leaderboardPageSize
    3: required i32 leaderboardOverlap
}

struct GuildLeaderboardSettings {
    1: required i32 leaderboardGracePeriodSeconds
    2: required i32 leaderboardPageSize
    3: required i32 leaderboardOverlap
}

struct LeaderboardReward
{
	1: required LeaderboardID leaderboardId
	2: required LeaderboardLeagueID leaderboardLeagueId
	3: required LeaderboardRibbonID leaderboardRibbonId

	13: required LootItemType rewardType
	14: required string rewardId
	15: required i32 rewardAmount
}

struct LeaderboardRibbon
{
	1: required LeaderboardID leaderboardId
	2: required LeaderboardLeagueID leaderboardLeagueId
	3: required LeaderboardRibbonID leaderboardRibbonId

	10: optional string localizedDisplay // EG: Platinum, Gold, Silver, Bronze, Ribbon A-Z
	9: required LocalizedString display

	11: required i32 positionStart // 1-base
	12: required i32 positionEnd // 1-base
	13: required AssetID trophyAssetId
	14: required AssetID bannerAssetId
	18: required string rewardChestAsset

	20: optional list<LeaderboardReward> rewards // Populated by mutator script

	30: optional i32 eventIslandTier
}

struct LeaderboardLeague
{
	1: required LeaderboardID leaderboardId
	2: required LeaderboardLeagueID leaderboardLeagueId

	30: optional map<LeaderboardRibbonID, LeaderboardRibbon> ribbons // Populated by mutator script

	9: required LocalizedString display

	11: required i32 displayOrder // Higher displayOrder means lower league.

	20: required i32 minPlayersPerDivision
	21: required i32 maxPlayersPerDivision
	22: required i32 initialDivisions
	23: required i32 incrementalDivisions
	24: required i32 daysLeftOverpack
	25: required i32 minPlacementCurrency
	26: required i32 maxPlacementCurrency

	35: required i32 promoteCount
	36: required i32 demoteCount
	37: required i32 promoteCurrencyCredit
	38: required i32 demoteCurrencyDeduction

	39: required list<i32> promoteCounts
	40: required list<i32> demoteCounts
	41: required list<i32> promoteCurrencyCredits
	42: required list<i32> demoteCurrencyDeductions

	50: optional AssetPath leagueBackground
	51: optional AssetPath leagueRibbon
}

struct Leaderboard
{
	1: required LeaderboardID leaderboardId

    10: required list<EventID> eventIds
    11: required EventPhases eventPhases
    12: required i32 showRank
    13: required i32 unlockRank
    14: required i32 hideRank
    15: required CurrencyID pointCurrencyId
    16: required CurrencyID placementCurrencyId

    29: required LocalizedString display
    30: optional LocalizedString rewardDisplay

    24: required LeaderboardLeagueID topLeagueId
    25: optional LeaderboardID topLeaderboardId

    40: required LocalizedString topLeagueText
    41: required LocalizedString middleLeagueText
    42: required LocalizedString bottomLeagueText
    43: required LocalizedString noLeagueText

    44: required LocalizedString previewText
    45: required LocalizedString recapText
    46: required LocalizedString joinText

    50: required RewardMessageID rewardMessageId

    21: optional map<LeaderboardLeagueID, LeaderboardLeague> leagues // Populated by mutator script

	60: required LeaderboardTemplateID leaderboardTemplateId
	61: required AssetPath tabIcon

	70: required AssetPath topRewardBannerBg
}

struct LeaderboardPlacement
{
	1: required CurrencyID currencyId

	10: required i32 minRank
	11: required i32 maxRank
	12: required i32 value
}

typedef string EventMenuWidgetID
struct EventMenuWidget
{
    1: required EventMenuWidgetID eventMenuWidgetId
    10: optional LocalizedString text
    15: required EventMenuWidgetType widgetType

    20: optional MessageButtonAction messageAction
    21: optional list<string> messageActionParameter

    30: required string portraitPosition
    31: optional string landscapePosition
    32: optional string anchorPoint

    // Tablet grid is slightly different, it is much larger so we are providing more fields for it.
    40: optional string tabletPortraitPosition
    41: optional string tabletLandscapePosition
    42: optional string tabletAnchorPoint

    50: optional i32 zOrder

    //Some custom parameter that we can use for each widget type
    //Play button will accept one parameter text
    60: optional list<string> parameters

    //Adding the concept of parenting so that we can do more fancy layouts in the future.
    70: optional string widgetName
    71: optional string widgetParent

    80: optional string portraitSizes
    81: optional string landscapeSizes
    82: optional string tabletPortraitSizes
    83: optional string tabletLandscapeSizes
}

struct LeaderboardTemplate
{
	1: required LeaderboardTemplateID leaderboardTemplateId
	2: required string luaFile
	3: required ColorID backgroundColor
	4: required AssetPath topBannerBg
	5: required string rewardsTemplateFile
	6: required AssetPath rewardsBg
	7: required AssetPath rewardsItemBg

	10: required AssetPath backButton
	11: required AssetPath leaderboardYouBg
	12: required AssetPath leaderboardYouTopBg

	13: required AssetPath tabBg
	14: required AssetPath tabSelectedImage

	15: required AssetPath middleTabSelectedImage
}

typedef string EventKeyDropRateFormulaID

// only
struct RarityEvoLevelKeyDropRate {
	1: required list<EventID> eventIds // PK
	2: required RarityID buildingRarity // PK
	3: required i32 buildingEvoLevel // PK
	4: optional EventKeyDropRateFormulaID formulaId // Adds extra probability from formula only when it is defined
	5: required double baseDropRate
	6: required CurrencyID currencyId
	7: required i32 currencyAmount
	8: required double socialDropRateIncrease
	9: required i32 socialCurrencyAmount
}

// Only
struct KeyDropRateByOrderTime
{
	1: required EventKeyDropRateFormulaID formulaId
	2: required i32 minOrderTimeInSecs
	3: required i32 maxOrderTimeInSecs
	4: required double dropRate
}

// Client+Server
struct EventBusinessKeyDropRate
{
	1: required BuildingID buildingId
	2: required list<EventID> eventIds
	3: optional CurrencyID currencyId // Deprecated, use currencyIds list
	4: optional i32 currencyAmount // Deprecated, use currencyAmounts list mutually exclusive with dropRateIncrease
	5: optional double dropRateIncrease
	6: required i32 socialCurrencyAmount
	7: optional string socialCurrencyId
	8: optional list<CurrencyID> currencyIds
	9: optional list<i32> currencyAmounts // mutually exclusive with dropRateIncrease
}

struct BuildingMultiplier
{
	1: required BuildingID buildingId
	2: required double eventPointMultiplier
	3: required list<EventID> eventIds
	4: required EventPhases eventPhases
}

//Tutorial
typedef string TutorialID
struct TutorialState
{
	1: required TutorialID tutorialId
}

typedef string AdminGiftMessageID
struct AdminGiftMessage
{
    1: required AdminGiftMessageID adminGiftMessageId
    10: required LocalizedString title
    11: required LocalizedString body
    12: required i32 priority
    13: required bool openable
    14: required bool claimOnClaimAll
    15: required list<EventID> eventIds
    16: required EventPhases eventPhases
    17: required i32 showRank
    18: required i32 hideRank
    19: required bool disabled
    22: required list<GiftMessageRewardID> giftMessageRewardIds
    30: optional LocalizedString openBody
    31: optional TemplateID templateId
}
// PopupMessages
typedef string PopupMessageID

enum AvailableOfferType
{
    Nothing = 0
    GachaOffer
    CardOffer
}

struct PopupMessage
{
    1: required PopupMessageID popupMessageId

    10: required i32 displayOrder
    12: optional TemplateID templateId

    21: required list<EventID> eventIds
    22: required EventPhases eventPhases
    23: required i32 showRank
    24: required i32 hideRank
    26: required bool instant

    30: required i32 repeatSeconds
    31: required i32 maxShown

    40: required bool disabled

    50: required AvailableOfferType offerType
    51: required string offerId
    52: required bool offerSingleStep	// if TRUE, show this message only if offer is at its exact step (ignoring stepup)
    53: optional i32 lastIAPMinutes

    60: required LocalizedString title
    61: required LocalizedString body

	70: optional LocalizedString body2 // Use for new popup template messagedialogv2.lua to display text at bottom of the popup
	71: optional LocalizedString title2 // Use for new popup template messagedialogv2.lua to display text below the main title

	80: optional LocalizedString leftRibbon // Use by new popup template messagedialogv3.lua for left ribbon text
	81: optional LocalizedString rightRibbon // Use by new popup template messagedialogv3.lua for right ribbon text
	82: optional LocalizedString bottomLeft // Use by new popup template messagedialogv3.lua for bottom left text
	83: optional LocalizedString bottomRight // Use by new popup template messagedialogv3.lua for bottom right text
	84: optional LocalizedString leftUnderRibbon // Use by new popup template messagedialogv3.lua for left ribbon text
	85: optional LocalizedString rightUnderRibbon // Use by new popup template messagedialogv3.lua for right ribbon text


	72: optional list<CurrencyID> requireOneOfCurrencyIds
	73: optional list<i32> requireOneOfCurrencyAmounts

	74: optional bool markAsReadOnClosing
	75: optional bool triggerButtonActionOnTappingCloseButton
	76: optional bool triggerButtonActionOnTappingOutside
}

struct PopupMessageSettings
{
    10: required i32 globalQueueMax
    11: required i32 globalQueueCooldownSeconds
}

struct EventSettings
{
	1: required EventIslandID defaultEventIslandId
}

struct PlayerDisplaySuggest
{
	1: required string display
}


// Guild Name Suggestion
struct GuildNameSuggest
{
    1: required string display
}

// Guild Leaderboard(s)

typedef string GuildLeaderboardID
typedef string GuildLeaderboardRibbonID

enum GuildLeaderboardRewardRecipient
{
    Everyone = 0,
    Leader
}

struct GuildLeaderboardReward
{
    1: required GuildLeaderboardID leaderboardId
    2: required GuildLeaderboardRibbonID leaderboardRibbonId
    3: required GuildLeaderboardRewardRecipient recipient

    13: required LootItemType rewardType
    14: required string rewardId
    15: required i32 rewardAmount
}

struct GuildLeaderboardRibbon
{
    1: required LeaderboardID leaderboardId
    2: required LeaderboardRibbonID leaderboardRibbonId

    4: required LocalizedString display

    5: required i32 positionStart // 1-base
    6: required i32 positionEnd // 1-base
    7: required AssetID trophyAssetId
    8: required AssetID bannerAssetId
    9: required string rewardChestAsset

    10: optional list<GuildLeaderboardReward> memberRewards // Populated by mutator script
    11: optional list<GuildLeaderboardReward> leaderRewards // Populated by mutator script
    // 12: optional i32 eventIslandTier
}

struct GuildLeaderboard
{
    1: required GuildLeaderboardID leaderboardId

    10: required list<EventID> eventIds
    11: required EventPhases eventPhases
    12: required i32 showRank
    13: required i32 unlockRank
    14: required i32 hideRank
    15: required CurrencyID pointCurrencyId

    29: required LocalizedString display
    30: optional LocalizedString rewardDisplay

    44: required LocalizedString previewText
    45: required LocalizedString recapText
    46: required LocalizedString joinText

    50: optional map<GuildLeaderboardRibbonID, GuildLeaderboardRibbon> ribbons // Populated by mutator script

    60: required RewardMessageID rewardMessageId
    61: required RewardMessageID leaderRewardMessageId

    70: required LeaderboardTemplateID leaderboardTemplateId // do we need this one ?
	71: required AssetPath tabIcon

	72: required AssetPath topRewardBannerBg

    80: optional LocalizedString myTeamMemberDisplay
	81: optional AssetPath myTeamMemberTabIcon
}

// Guilds

struct GuildMemberTypeDisplay
{
    1: required GuildMemberType guildMemberType
    2: required LocalizedString display
    3: required i32 displayOrder
	4: optional LocalizedString displaySingular

    20: required string iconImagePath

	50: optional LocalizedString promoteFormat
	51: optional LocalizedString demoteFormat
	52: optional LocalizedString kickMemberFormat
	53: optional LocalizedString makeLeaderFormat
}

struct GuildJoinTypeDisplay
{
    1: required GuildJoinType guildJoinType
    2: required LocalizedString display
    3: required i32 displayOrder
	4: optional LocalizedString displayA
	5: optional LocalizedString displayB
}

struct GuildSettings
{
    10: required i32 maxMemberCount // Default max count
    11: required i32 maxChatHistory
    12: required i32 unlockRank
    16: required i32 createRank
    17: required GuildMemberType guildLeaderType
    18: required GuildMemberType guildCoLeaderType
    19: required i32 maxInvitations

    20: required i32 maxDisplayLength
    21: required i32 maxDisplayTagLength
    22: required i32 maxDescriptionLength
    23: required i32 minDisplayLength
    24: required i32 minDisplayTagLength
    25: required i32 minDescriptionLength

    30: required i32 onlineStatusActivityMinutes
    31: required i32 maxChatDisplayHistory
    32: required string chatAllowedCharacters

    // Location
    40: required LocationID unknownLocationId
    41: required LocationID anyLocationId

    // Emblem / Frames
    42: required GuildEmblemID noEmblemId
    43: required AssetID defaultFrameAssetId
    44: required AssetID noGuildDefaultFrameAssetId

    // Suggested Guilds
    50: required i32 suggestTargetGuildCount
    51: required i32 suggestBucketsPerLocation
    52: required double suggestOverfetchMultiplier
    53: required i32 suggestDeadGuildInactivityMinutes
    54: required double suggestAutoJoinRatio

    // Guild Message Reward Currencies
    60: required CurrencyID promotionTokenCurrencyID
    61: required CurrencyID demotionTokenCurrencyID
    62: required CurrencyID leaderTokenCurrencyID
    63: required list<GuildMemberType> canSendGuildInvites

    // Guild Strings
    90: required LocalizedString joinInvitationDefault                // 0 = player name, 1 = guild name, 2 = guild tag
    91: required LocalizedString joinApplicationDefault
    92: required LocalizedString applicantAcceptedMessageTitle
    93: required LocalizedString applicantRejectedMessageTitle
    94: required LocalizedString cannotSendGuildInvitesText
	95: optional LocalizedString cannotJoinFullGuildText
	96: optional LocalizedString guildDisplayAndTagTakenText
	97: optional LocalizedString guildNameTakenText
	98: optional LocalizedString guildTagTakenText
	99: optional LocalizedString guildDeletedText
	100: optional LocalizedString guildErrorText

	200: optional i32 askForItemsSecondsTTL // How long an askForItems request will last
	210: required BuildingID guildHallBuildingId
}

typedef string LocationID
struct Location
{
    1: required LocationID locationId
    2: required LocalizedString display
    3: optional AssetID imageAssetId
    4: required string imagePath
    5: required i32 displayOrder
    6: required i32 section
	7: optional LocationID altLocationId
	8: optional LocalizedString shortDisplay

    10: required bool hideInUi
    11: required string analyticsLabel
    12: required list<string> languages
}

typedef string GuildEmblemID
struct GuildEmblem
{
    1: required GuildEmblemID guildEmblemId
    2: required string imagePath
    3: required i32 displayOrder

    10: required bool hideInUi

    20: optional i32 minGuildRank
}

struct GuildBoundItem
{
    1: required LootItemType itemType
    2: required string itemId
}

typedef string ChatSystemMessageID

struct ChatSystemMessage
{
    1: required ChatSystemMessageID chatSystemMessageId
    2: required LocalizedString message
}

typedef string GiftID

struct Gift
{
    1: required GiftID giftId

    10: required LocalizedString display
    11: required AssetID iconAssetId
    12: required LocalizedString description
    13: required i32 displayOrder
    // (client) 14: required RarityID minRarityId	// can be 0, which means none
    // (client) 15: required RarityID maxRarityId	// can be 0, which means none

    30: required AssetID gachaRevealFXAssetId

    40: required list<LootTableID> lootTableIds
    41: required list<i32> lootTableSpins

    50: required bool openable
    51: required bool claimable

    70: optional list<EventID> eventIds
    71: optional EventPhases eventPhases
}

struct GearAvailableOnGachaOfferList
{
	1: required CurrencyID currencyId
	10: required list<GachaOfferID> gachaOfferIds
}

struct GearAvailableOnCardOfferList
{
	1: required CurrencyID currencyId
	10: required list<CardOfferID> cardOfferIds
}

struct GearAvailableOnLevelList
{
	1: required CurrencyID currencyId
	10: required list<LevelID> levelIds
}

struct GearAvailableOnBusinessHarvestList
{
	1: required CurrencyID currencyId
	10: required list<BuildingID> businessIds
}

typedef string MainShopEntryID

struct MainShopEntry
{
    1: required MainShopEntryID mainShopEntryId
    10: optional GachaOfferID gachaOfferId
    11: optional StoreID storeId
    12: required i32 orderIndex
    13: required i32 showRank
    14: required i32 unlockRank
    15: required i32 hideRank
}

typedef string AskForItemID

struct AskForItemEntry
{
    1: required AskForItemID askForItemId

    10: optional CurrencyID currencyId        // requested currency Id (e.g.: gold)
    11: optional i32 currencyAmount           // requested amount

    20: optional CurrencyID costCurrencyId    // cost for sending help (e.g.: gold_gift)

    30: optional CurrencyID rewardCurrencyId  // reward for sending help (e.g.: palpoints)
    31: optional i32 rewardCurrencyAmount     //

    40: optional i32 helpLimit                      // max amount that a single guild mate can give you. This is the amount received.
}

typedef string TestBucketID

struct TestBucket
{
    1: required TestBucketID testBucketId
    2: required i32 priority
    3: optional set<TestBucketID> conflictingTestBucketIds
    4: optional string overridesString

    // Overrides
    11: optional Settings settings
    12: optional StartingGameState startingGameState

    // Store and Gacha overrides
    100: optional map<StoreProductID, StoreProduct> storeProducts
    110: optional map<StoreProductID, VendorProduct> vendorProducts
    200: optional map<GachaOfferID, GachaOffer> gachaOffer
    201: optional map<RankID, Rank> rank
    // Levels
	// DEPRECATED: Use newLevel
	202: optional map<LevelID, Level> level (deprecated="true")
	300: optional map<LevelID, NewLevel> newLevel
    203: optional map<BoostID, Boost> boost
    204: optional map<LevelDotID, LevelDot> levelDot
    205: optional map<VillainID, Villain> villain
    206: optional map<LevelName, MatchThreeData> matchThreeData

    // Achievements
    207: optional map<AchievementID, Achievement> achievement
    208: optional map<AchievementGroupID, AchievementGroup> achievementGroup

    //Tutorial
    209: optional list<TutorialState> tutorialStates

    // TODO Popup Messages Enable when adding Excel file
    210: optional map<PopupMessageID, PopupMessage> popupMessages
    211: optional PopupMessageSettings popupMessageSettings
    212: optional map<LevelCampaignID, LevelCampaign> levelCampaigns

    // New stores
    220: optional map<StoreID, Store> stores
    221: optional map<StoreID, list<StoreInventoryItem>> storeInventories
    222: optional map<CardOfferID, CardOffer> cardOffers
    223: optional map<IAPProductID, IAPProduct> iapProducts
    224: optional map<QuestID, Quest> quests

}
// AB Test (Temporary until we have a butler service to do this segmentation)
typedef string ABTestID

struct ABTest
{
	1: required ABTestID abTestId
	2: required TestBucketID testBucketId
	10: required i32 weight
	11: optional bool enabled
}
struct ClientVersionTestBucket
{
	1: required ABTestID overrideId
	2: required TestBucketID testBucketIdOldVersion
	3: required TestBucketID testBucketIdNewVersion
	10: optional bool enabled
}


// Heroes

typedef i32 HeroTypeID

struct HeroType
{
	1: required HeroTypeID heroTypeId
	11: required LocalizedString display
	12: required AssetID iconAssetId

	20: required i32 displayOrder
	21: required bool hideInUi
}

// Hero Level Curves

typedef string HeroLevelCurveID

struct HeroLevelCurve
{
	1: required HeroLevelCurveID heroLevelCurveId
	10: required i32 xp
	11: required string display
}

// HeroMax Upgrade Curve

struct HeroMaxUpgrade
{
	1: required i32 amount
	2: required CurrencyID currencyId
	3: required i32 currencyAmount
}

struct Hero
{
	1: required HeroID heroId
	//2: required HeroTypeID heroTypeId

	15: required LocalizedString display
	16: required LocalizedString description
	17: optional AssetID boardIconImage
	18: optional AssetID boardIconImage2

	//12: required AssetID fxAssetId
	//13: required AssetID gachaRevealFXAssetId
	//28: optional AssetID gachaBoxRevealFXAssetId
	//14: required i32 sequenceId

	20: required AffinityID affinityId
	21: optional RarityID rarityId	// Deprecated - rarity should come from business
	22: required SpecialtyID specialtyId
	//22: required list<HeroTypeID> heroTypeIds
	//24: required RarityID maxRarityId
	25: optional SkillID leaderSkillId
	26: optional SkillID activeSkillId
	27: optional list<SkillID> additionalSkillIds

	30: optional i32 raidBossBaseValueMultiplier

	//30: required i32 attackBase
	//31: required double attackGrowth
	//32: required i32 healthBase
	//33: required double healthGrowth
	//34: required i32 recoveryBase
	//35: required double recoveryGrowth

	//40: required HeroLevelCurveID heroLevelCurveId
	//41: required i32 sellBase
	//42: required double sellGrowth
	//43: required i32 feedXpBase
	//44: required double feedXpGrowth
	//45: required i32 affinityXpBase
	//46: required double affinityXpGrowth
	//47: required CurrencyID sellCurrencyId

	//51: required FortunesFavorID fortunesFavorFusionConfig

	//60: required bool hideInUi
	//61: required AwakeningCurveID awakeningCurveId
	//62: required i32 awakeningMaxLevel
	//63: required list<HeroID> awakeningAlternateHeroIds

	//70: required HeroPvpTypeID heroPvpTypeId
	//71: required list<EnemySkillID> defenderSkillIds
	//72: required list<SkillID> counterSkillIds
}

typedef string RaidBossID
typedef string RaidBossActivityID
typedef string SkillID
typedef string HeroID

struct RaidBoss
{
	1: required RaidBossID raidBossId
	2: required RaidBossActivityID raidBossActivityId

	5: required LocalizedString display

	10: required list<EventID> eventIds
	11: required list<LevelID> levelIds
	// i dont understand this field in legendary
	//12: required KeyCostPerLevelID keyCostPerLevelId
	13: required AffinityID affinityId	// Order color
	14: required SpecialtyID specialtyId	// Order type
	15: optional i32 orderSize	// Deprecated already! In favor of orderSizeCurveId
	16: optional i32 maxBakers	// Deprecated already! In favor of maxHeroes
	17: optional i32 maxHeroes

	30: optional i32 baseCollectValue	// Awarded if cell affinity matches boss affinity
	33: optional list<i32> baseOrdersPerDonut
	31: optional i32 affinityBonus		// Additional multiplier per hero
	32: optional i32 specialtyBonus		// Additional multiplier per hero
	50: optional RaidBossCurveID orderSizeCurveId

	//12: required AssetID environmentAssetId
	//13: required AssetID musicAssetId
	//14: required list<double> affinityPercentageInitial
	//15: required list<double> affinityPercentageGeneral

	//11: required list<HeroTypeID> heroTypeIds

	//16: required i32 turn
	//17: required i32 initialTurn
	//18: required EnemyFormationID enemyFormationId
	19: required i32 battleTimerSeconds

	//20: required i32 lifespanSeconds

	//81: required i64 attack
	//82: required i64 defense
	//83: required i64 health

	//24: required double attackGrowth
	//25: required double defenseGrowth
	//26: required double healthGrowth

	//27: required list<EnemySkillID> skillIds
	//28: required list<RaidBossObjectiveID> objectiveIds
	//29: required list<RaidBossRewardID> rewardIds

	//31: required AssetID heroAssetId
	//32: required AssetID enemyFxAssetId
	//33: required AssetID deathFxAssetId
	//37: required RaidBossRarityID raidBossRarityId
	//38: required AssetID heroBackgroundAssetId

	//40: required list<TemplateID> templateIds
	//41: optional list<TemplatePrefetch> templatePrefetch // Filled in by mutator

	//50: required RaidBossCurveID attackCurveId
	//51: required RaidBossCurveID defenseCurveId
	//52: required RaidBossCurveID healthCurveId
	53: required i32 levelMin
	54: required i32 levelMax
	59: optional i32 levelForced
	55: required i32 maxParticipants
	56: required i32 maxImpressions
	57: required double spawnWeight
	58: required bool guildOnly

	//60: optional list<SituationID> situationIds

	//70: required CurrencyID battleEnergyId		// rechargeable BE
	//71: required i32 battleEnergyCost
	//72: required i32 powerAttackEnergyCost
	//73: required double powerAttackDamageMultiplier
	74: optional CardOfferID battleEnergyCardOfferId // To purchase non-rechargeable BEP
}

typedef string RaidBossCurveID

struct RaidBossCurve
{
	1: required RaidBossCurveID raidBossCurveId
	2: required i32 level
	// lua doesn't support thrift doubles
	3: required i32 multiplier
}

//struct RaidBossKarmaLimit
//{
//	1: required RaidBossActivityID raidBossActivityId
//	2: required list<EventID> eventIds
//	3: required i32 maxKarma
//}

typedef string RaidBossObjectiveID

struct RaidBossObjective
{
	1: required RaidBossObjectiveID raidBossObjectiveId
	2: required RaidBossObjectiveType type

	9: required LocalizedString display

	11: required i32 displayOrder
	13: required LocalizedString details
}

typedef string RaidBossRarityID
struct RaidBossRarity
{
	1: required RaidBossRarityID raidBossRarityId

	9: required LocalizedString display

	11: required AssetID chestId
	12: required AssetID avatarFrameId
}

typedef string RaidBossRewardID
struct RaidBossReward
{
	1: required RaidBossRewardID raidBossRewardId
	2: required LootItemType rewardType
	3: required string rewardItemId
	4: required i32 rewardBase
	// lua doesn't support thrift doubles
	5: required double rewardGrowth
	6: required RaidBossCurveID rewardCurveId
}

struct RaidBossKarmaBracket
{
	1: required RaidBossActivityID raidBossActivityId

	10: required i32 minKarma
	11: required i32 maxKarma
	20: required i32 minNotAttacked
	21: required i32 maxNotAttacked
	// lua doesn't support thrift doubles
	22: required double stdDev
	23: required i32 stdDevCutOff
	24: required i32 karmaIncrement
	25: required i32 karmaDecrement
	26: required i32 mvpKarmaIncrement
	// lua doesn't support thrift doubles
	27: required double fairShareMultiplier
}

typedef string RaidBossDifficultyBracketID
struct RaidBossDifficultyBracket
{
	1: required RaidBossActivityID raidBossActivityId
	2: required RaidBossDifficultyBracketID raidBossDifficultyBracketId

	10: required i32 minDifficulty
	11: required i32 maxDifficulty

}

// Data
struct Data
{
    // General
    1: required map<RankID, Rank> rank

    4: required map<CurrencyID, Currency> currency
    11: required map<EventLockID, EventLock> eventLock
    13: optional Settings settings
    14: optional StartingGameState startingGameState
    93: optional map<EntityID, StartingKingdomEntity> startingKingdomEntities
    // Assets and bundles
    17: required map<BundleID, list<ConfigBundle>> bundlesConfig
    19: optional map<BlobID, LevelBlob> levelBlobs
	300: optional map<BundleID, list<ConfigBundle>> resolutionBundles  // Deprecated on 1.1.28, as we are no longer supporting hd and ld bundles anymore.
	310: optional BundleManifest bundleManifest
	320: optional BundleManifest resolutionManifests // Deprecated on 1.1.28, as we are no longer supporting hd and ld bundles anymore.
	330: optional BundleManifest localizationManifests

	// Junk Food
    20: required map<BuildingID, Building> building
    21: required map<RecipeID, Recipe> recipe
    24: required map<DecoID, Deco> deco
    25: required map<BusinessID, Business> business
	26: optional map<BusinessOrderID, BusinessOrder> businessOrder (deprecated="true")
    27: required map<i32, InventoryTab> inventoryTab
	28: required map<BuildingID, Blocker> blockers

    // Gacha
    32: required map<WeightedLootListID, list<WeightedLoot>> weightedLootList

    34: required map<RarityID, Rarity> rarity //Deprecated in 1.1.27 -- still used on s_erver
    //Since we updated build menu, we need to define a new rarity so that both old and new could work during the submission config phase
    35: optional map<RarityID, Rarity> newRarity

    // Levels
	// DEPRECATED: new newLevel
    40: required map<LevelID, Level> level (deprecated="true") // ready to be removed on at least build >= #1957
    41: required map<BoostID, Boost> boost
    42: optional map<LevelDotID, LevelDot> levelDot		// Deprecated on 1.1.28. This used to be used by recipe islands
	43: optional map<VillainID, Villain> villain
	44: optional map<LevelName, MatchThreeData> matchThreeData
	45: optional map<LevelID, NewLevel> newLevel
    46: required map<LevelDotID, LevelDotV2> newLevelDot	// New simplified level dots to be used on the new event map


	// Evolve Materials
	55: required map<MaterialID, Material> material

	// Island
	60: required map<IslandID, Island> island
	61: optional IslandSettings islandSettings
	63: optional map<IslandObjectID, IslandObject> islandObject (deprecated="true")
	64: optional map<ColorID, Color> color

	70: required map<ExpansionID, Expansion> expansion
	71: required map<ExpansionTypeID, ExpansionType> expansionType

	// New gacha stuff
	74: required map<GachaGroupID, GachaGroup> gachaGroup
	75: required map<GachaOfferID, GachaOffer> gachaOffer
	76: required map<GachaPackID, GachaPack> gachaPack
	77: required map<LootTableID, list<LootTable>> lootTable
	78: required map<LootCurrencyGroupID, list<LootCurrencyGroup>> lootCurrencyGroup
	79: required map<LootBuildingGroupID, list<LootBuildingGroup>> lootBuildingGroup

	80: required map<AvatarID, Avatar> avatar

	130: optional map<AdminMessageID, AdminMessage> adminMessages
	131: required list<AdminGiftMessage> adminGiftMessages

	140: required map<AnalyticsEventID, AnalyticsEvent> analyticsEvents
	141: required map<AnalyticsEventID, AppBoyEvent> appBoyEvents
	142: required map<AnalyticsDimensionID, AnalyticsDimension> analyticsDimensions
	143: optional map<AnalyticsEventID, ApsalarEvent> apsalarEvents

	150: optional map<BusinessOrderListID, BusinessOrderList> businessOrderList (deprecated="true")
	152: required map<EvolutionMaterialID, BusinessEvolution> businessEvolution

	// NPC
	160: required map<NpcID, Npc> npc

	// store
	170: required map<StoreProductID, VendorProduct> vendorProducts
	180: required map<StoreProductID, StoreProduct> storeProducts

	200: required map<MarketOrderID, BuyItemOrder> buyItemOrder
	201: required map<MarketType, Market> marketType

    202: required  map<ClientPlatform, ForcedUpgrade> forcedUpgrade
    203: required map<ErrorId, ErrorMessage> errorMessage

    // Achievements
    204: optional map<AchievementID, Achievement> achievement
    205: optional map<AchievementGroupID, AchievementGroup> achievementGroup

    // Test Buckets
    210: required map<TestBucketID, TestBucket> testBuckets

    // Stranger Settings
    220: required StrangerSettings strangerSettings
    221: required list<StrangerMatchSettings> strangerMatchSettings (deprecated="true") // ready to be removed on at least build >= #1957
    222: required list<FakeStrangerDisplay> fakeStrangerDisplays (deprecated="true") // ready to be removed on at least build >= #1957

    223: required map<GiftMessageRewardID, GiftMessageReward> giftMessageRewards
    224: required list<PartialKingdomLikeGift> partialKingdomLikeGifts (deprecated="true") // ready to be removed on at least build >= #1957
    225: required map<KingdomLikeGiftID, KingdomLikeGift> kingdomLikeGifts

    226: optional map<PushMessageID, PushMessage> pushMessages

	229: optional map<SocialUnlockRewardID, SocialUnlockReward> socialUnlockrewards

	400: optional list<AdProvider> adProviders

	500: required list<PopupTemplate> popupTemplate
	501: required map<PopupTemplateType, DefaultTemplate> defaultTemplate
	502: required list<RushCostByRemainingTime> rushCostsByRemainingTime
	503: optional map<PopupMessageID, list<MessageTemplateModifier>> messageTemplateModifiers

	600: optional map<GachaBannerID, GachaBanner> gachaBanner

	601: optional map<PresetKingdomID, list<PresetKingdomEntity>> presetKingdoms
	// AB Tests
	602: optional map<ABTestID, list<ABTest>> abTests
	603: optional map<ABTestID, ClientVersionTestBucket> clientVersionTestBuckets

	// DEPRECATED - remove from configs once 0.1.5 is live
	610: optional map<BuildMenuSpecialCardID, BuildMenuSpecialCard> buildMenuSpecialCard  (deprecated="true") // ready to be removed on at least build >= #1957

	// Below are all new settings in Settings.xslx
	700: optional BusinessMenuSettings businessMenuSettings

    790: required map<RewardMessageID, RewardMessage> rewardMessages

    800: required map<EventID, Event> events;
    810: required map<LeaderboardID, Leaderboard> leaderboards
    811: required LeaderboardSettings leaderboardSettings
    812: optional list<LeaderboardLeague> leaderboardLeagues // Temporary, used by Mutator script.
    813: optional list<LeaderboardRibbon> leaderboardRibbons  // Temporary, used by by Mutator script.
    814: optional list<LeaderboardReward> leaderboardRewards  // Temporary, used by by Mutator script.
    815: required map<CurrencyID, list<LeaderboardPlacement>> leaderboardPlacements

    816: required list<RarityEvoLevelKeyDropRate> rarityEvoLevelKeyDropRates
    817: required map<EventKeyDropRateFormulaID, list<KeyDropRateByOrderTime>> keyDropRateByOrderTime
    818: required map<BuildingID, EventBusinessKeyDropRate> eventBusinessKeyDropRates

	820: optional map<LeaderboardTemplateID, LeaderboardTemplate> leaderboardTemplates

    850: required map<EventIslandID, EventIsland> eventIslands
    851: required map<EventHowToPlayID, EventHowToPlay> eventHowToPlays
    852: required map<EventMainMenuID, EventMainMenu> eventMainMenus

    900: required map<CastleActivityID, CastleActivity> castleActivities

	// Suggest nickname
	901: required list<PlayerDisplaySuggest> playerDisplaySuggestStart
	902: required list<PlayerDisplaySuggest> playerDisplaySuggestMiddle
	903: required list<PlayerDisplaySuggest> playerDisplaySuggestEnd

    //Tutorial
    910: required list<TutorialState> tutorialStates

    // TODO Popup Messages Enable when adding Excel file
    911: required map<PopupMessageID, PopupMessage> popupMessages
    912: required PopupMessageSettings popupMessageSettings

	1000: optional EventSettings eventSettings

	// For analytics purpose, this will contain a mapping of luaFilename/event to analytics
	1100: optional list<ScreenNameMapping> screenNameMapping
	1101: optional map<CellInfoMapID, list<CellInfo>> cellInfo

	1200: optional map<KeyCostPerLevelID, list<KeyCostPerLevel>> keyCostPerLevel
	1201: optional list<PlayerMatchRankSettings> playerMatchRankSettings

	1202: required map<BuildingID, BuildingMultiplier> buildingMultipliers

    // Guild Leaderboards
    1300: required GuildLeaderboardSettings guildLeaderboardSettings
    1301: optional map<GuildLeaderboardID, GuildLeaderboard> guildLeaderboards
    1302: optional list<GuildLeaderboardRibbon> guildLeaderboardRibbons  // Temporary, used by by Mutator script.
    1303: optional list<GuildLeaderboardReward> guildLeaderboardRewards  // Temporary, used by by Mutator script.

    // Guild
    1311: required map<LocationID, Location> locations
    1312: required GuildSettings guildSettings
    1313: required map<GuildMemberType, GuildMemberTypeDisplay> guildMemberTypeDisplays
    1314: required map<GuildJoinType, GuildJoinTypeDisplay> guildJoinTypeDisplays
    1315: required map<GuildEmblemID, GuildEmblem> guildEmblems
    1316: required list<GuildBoundItem> guildBoundItems
    1317: required map<GuildRankID, GuildRank> guildRank

    // Chat System Messages
    1330: required map<ChatSystemMessageID, ChatSystemMessage> chatSystemMessages

    1400: required map<GiftID, Gift> gifts
    1410: optional PollSettings pollSettings

    // Suggest guild name
    1500: required list<GuildNameSuggest> guildNameSuggestStart
    1501: required list<GuildNameSuggest> guildNameSuggestMiddle
    1502: required list<GuildNameSuggest> guildNameSuggestEnd

    1600: required map<QuestID, Quest> quests
    1601: optional list<Goal> questGoals // Temporary, used by Mutator script.

    1610: required map<QuestID, Quest> questTemplates
    1611: optional list<Goal> questGoalTemplates // Temporary, used by Mutator script.

    1602: required map<QuestNpcID, QuestNpc> questNpc
    1603: required map<BuildingID, BusinessQuestNpc> businessQuestNpc

    1700: optional HappinessSettings happinessSettings
    1710: required map<StoreID, Store> stores
    1711: required map<StoreID, list<StoreInventoryItem>> storeInventories
    1712: required map<CardOfferID, CardOffer> cardOffers
    1713: required map<IAPProductID, IAPProduct> iapProducts


	// Campaigns
	1899: required CampaignSettings campaignSettings
    1900: required map<LevelCampaignID, LevelCampaign> levelCampaigns
    1901: optional map<LevelCampaignID, BusinessLevelsList> businessLevelIdsLookup // Populated by Mutator script.
    1902: optional map<LevelCampaignID, CastleEventLevelsList> castleEventLevelIdsLookup // Populated by Mutator script.
    1903: optional map<LevelCampaignID, LevelCampaignLevelsList> campaignLevelIdsLookup // Populated by Mutator script.
    1904: required map<LevelCampaignStyleID, LevelCampaignStyle> levelCampaignStyles

    2014: required map<BuildingType, BuildingTypeLocalization> buildingTypeLocalizations

	// FTUE Settings
    3000: optional FTUESettings ftueSettings

    3301: optional map<Match3ThemeId, list<MatchThreeCellDefinition>> matchThreeCellDefinitions
	3302: optional map<Match3ThemeId, list<MatchThreeBlasterDefinition>> matchThreeBlasterDefinitions

    2000: required list<GoalDisplayTemplate> goalDisplayTemplates
    2001: required map<GoalType, list<QuestDisplayTemplate>> questTitles
    2006: required QuestSettings questSettings
    2015: required map<RankID, QuestRankSettings> questRankSettings
    2016: required map<BusinessOrderID, NewBusinessOrder> newBusinessOrders
    2100: optional map<EventMenuWidgetID, EventMenuWidget> eventMenuWidgets
    // Where to find gear list. Populated by mutator script
    6100: optional map<CurrencyID, GearAvailableOnGachaOfferList> gearAvailableOnGachas
    6101: optional map<CurrencyID, GearAvailableOnCardOfferList> gearAvailableOnCardOffers
    6102: optional map<CurrencyID, GearAvailableOnLevelList> gearAvailableOnLevels
    6103: optional map<CurrencyID, GearAvailableOnBusinessHarvestList> gearAvailableOnBusinessHarvest

    7100: required map<MainShopEntryID, MainShopEntry> mainShopEntries

    8000: optional map<AskForItemID, AskForItemEntry> askForItems

    8001: optional map<StoreTabID, StoreTab> storeTabs

    8100: optional map<GuildQuestRewardID, list<GuildQuestReward>> guildQuestRewards

	// Raid Boss
	2200: optional map<RaidBossID, RaidBoss> raidBosses
	2201: optional map<RaidBossActivityID, RaidBossActivity> raidBossActivities
	2202: optional map<RaidBossObjectiveID, RaidBossObjective> raidBossObjectives
	2203: optional map<RaidBossActivityID, list<RaidBossKarmaBracket>> raidBossKarmaBrackets
	2204: optional map<RaidBossActivityID, list<RaidBossDifficultyBracket>> raidBossDifficultyBrackets
	2205: optional map<RaidBossCurveID, list<RaidBossCurve>> raidBossCurves
	2206: optional map<RaidBossRewardID, list<RaidBossReward>> raidBossRewards
	2207: optional map<RaidBossRarityID, RaidBossRarity> raidBossRarities
	//2208: optional map<RaidBossActivityID, list<RaidBossKarmaLimit>> raidBossKarmaLimits

	// Heroes
	2220: optional map<HeroID, Hero> heroes
}
